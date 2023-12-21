#include "CodesTable.h"
#include <iostream>

CodesTable::CodesTable()
{
	this->size = 256;
}

void CodesTable::addCode(unsigned char c, string code)
{
	codesTable[c] = code;
}

string CodesTable::getCode(unsigned char c)
{
	return this->codesTable[c];
}

unsigned char CodesTable::getChar(string code) {
	unsigned char ch = 0;
	while (code != this->codesTable[ch])
	{
		ch++;
	}
	return ch;
}

bool CodesTable::hasLetter(string code){
	for (int i = 0; i < 256; i++)
	{
		if (this->codesTable[i] == code)
		{
			return true;
		}
	}
	return false;
}

