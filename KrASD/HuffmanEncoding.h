#pragma once
#include "HuffmanTree.h"
class HuffmanEncoding
{
private:
	HuffmanTree* tree;
	char* filename;
public:
	HuffmanEncoding(char* filename);
	void encode(char* toFileName);
	void decode(char* fromFileName, char* toFileName);
};

