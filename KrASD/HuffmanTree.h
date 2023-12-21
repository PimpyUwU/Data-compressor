#pragma once
#include "Heap.h"
#include "CodesTable.h"

class HuffmanTree
{
public:
	HuffmanTree();
	HuffmanTree(char* filename);
	HuffmanTree(unsigned int* frequencies);
	void buildTree();
	Node* getTreeRoot();
	void BuildHuffmanTable(Node* node, string code);
	CodesTable* getTable();
	Heap getHeap();
private:
	CodesTable* Table;
	Heap inputHeap;
	Node* root;
	Node** getMin(Node** heapArr, int size);
};


