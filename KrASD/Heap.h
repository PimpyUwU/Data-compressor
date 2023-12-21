#pragma once
#include "Node.h"
#include "FrequencyTable.h"
#include <iostream>
using namespace std;
class Heap
{
public:
	Heap();
	Heap(char* filename);
	Heap(unsigned int* frequencies);
	void calculateSize(FrequencyTable table);
	void readTable(FrequencyTable table);
	void HeapSort(Node** arr, int N);
	int getSize();
	Node** getHeap();
	unsigned int* getFrequencies();
private:
	Node** heap;
	FrequencyTable table;
	int size;
	void Swap(Node*& a, Node*& b);
	void Heapify(Node** arr, int N, int i);
};

