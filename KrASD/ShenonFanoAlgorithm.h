#pragma once
#include "Heap.h"
#include "CodesTable.h"

class ShenonFanoAlgorithm
{
private:
	CodesTable* table;
	Heap inputHeap;
	void BuildShenonFanoTable();
	void CalculateCodeRecursive(string code, Node** start, Node** end);
	Node** getMid(Node** start, Node** end);
public:
	ShenonFanoAlgorithm();
	ShenonFanoAlgorithm(char* filename);
	ShenonFanoAlgorithm(unsigned int* frequencies);
	unsigned int* getFrequencies();
	CodesTable* getCodesTable();
};

