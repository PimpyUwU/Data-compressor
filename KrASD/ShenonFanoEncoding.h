#pragma once
#include "ShenonFanoAlgorithm.h"
class ShenonFanoEncoding
{
private:
	ShenonFanoAlgorithm* sf;
	char* filename;
public:
	ShenonFanoEncoding(char* filename);
	void encode(char* toFileName);
	void decode(char* toFileName, char* fromFileName);
};

