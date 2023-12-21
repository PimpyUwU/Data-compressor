#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class LZWEncoding {
private:
    char* filename;
public:
    LZWEncoding(char* filename) : filename(filename) {}
    void encode(char* toFilename);
    void decode(char* fromFilename, char* toFilename);
};
