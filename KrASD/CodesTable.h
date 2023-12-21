#pragma once

#include <string>
using namespace std;

class CodesTable{
private:
     string codesTable[256];
     int size;
public:
    CodesTable();
    void addCode(unsigned char symbol, string code);
    string getCode(unsigned char symbol);
    unsigned char getChar(string code);
    bool hasLetter(string code);
};
