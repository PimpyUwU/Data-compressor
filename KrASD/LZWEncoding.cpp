#include "LZWEncoding.h"
#include <bitset>
using namespace std;

void LZWEncoding::encode(char* toFilename) {
    ifstream inputFile(this->filename, ios::binary);
    ofstream outputFile(toFilename, ios::binary | ios::out);

    map<string, int> dictionary;
    for (int i = 0; i <= 255; i++) {
        string ch = string(1, i);
        dictionary[ch] = i;
    }

    string p = "", c = "";
    p += inputFile.get();
    int dictSize = 256;
    int currentBits = 9;

    while (inputFile.peek() != EOF) {
        if ((dictSize & (dictSize - 1)) == 0) {
            currentBits++;
        }

        c += inputFile.get();
        if (dictionary.count(p + c) != 0) {
            p = p + c;
        }
        else {
            short value = dictionary[p];
            outputFile.write(reinterpret_cast<const char*>(&value), sizeof(value));
            if (dictSize < 4096) {
                dictionary[p + c] = dictSize++;
            }
            p = c;
        }
        c = "";
    }

    if (!p.empty()) {
        short value = dictionary[p];
        outputFile.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
    inputFile.close();
    outputFile.close();
}

void LZWEncoding::decode(char* fromFilename, char* toFilename) {
    ifstream inputFile(fromFilename, ios::binary);
    ofstream outputFile(toFilename, ios::binary | ios::out);

    vector<string> dictionary(4096);
    for (int i = 0; i <= 255; i++) {
        dictionary[i] = string(1, i);
    }

    int dictSize = 256;
    int currentBits = 9;

    short code;
    inputFile.read(reinterpret_cast<char*>(&code), sizeof(code));
    string s = dictionary[code];
    outputFile << s;

    while (inputFile.peek() != EOF) {
        if ((dictSize & (dictSize - 1)) == 0) {
            currentBits++;
        }

        short nextCode;
        inputFile.read(reinterpret_cast<char*>(&nextCode), sizeof(nextCode));
        string entry;

        if (nextCode >= dictSize) {
            entry = s + s[0];
        }
        else {
            entry = dictionary[nextCode];
        }

        if (dictSize < 4096) {
            dictionary[dictSize++] = s + entry[0];
        }
        s = entry;
        outputFile << s;
    }

    inputFile.close();
    outputFile.close();
}
