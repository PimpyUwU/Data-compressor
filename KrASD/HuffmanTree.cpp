#include "HuffmanTree.h"

HuffmanTree::HuffmanTree(){}

HuffmanTree::HuffmanTree(char* filename)
{
	inputHeap = *(new Heap(filename));
	buildTree();
	this->Table = new CodesTable();
	BuildHuffmanTable(this->root, "");
}

HuffmanTree::HuffmanTree(unsigned int* frequencies)
{
	inputHeap = *(new Heap(frequencies));
	buildTree();
	this->Table = new CodesTable();
	BuildHuffmanTable(this->root, "");
}

void HuffmanTree::buildTree()
{
	Node** heap = inputHeap.getHeap();
	int size = inputHeap.getSize();

	//pointer to smallest letter
	Node** smallestLetter;
	Node* parentalNode;

	parentalNode = new Node();
	parentalNode->setLeft(heap[0]);
	heap[0] = NULL;
	parentalNode->setRight(heap[1]);
	heap[1] = NULL;
	parentalNode->setLetter(new Letter(' ', parentalNode->getLeft()->getLetter()->getFrequency() + parentalNode->getRight()->getLetter()->getFrequency()));
	heap[0] = parentalNode;

	int j = 0;
	for (int i = 0; i < size - 3; i++) {
		parentalNode = new Node();
		smallestLetter = getMin(heap, size);
		parentalNode->setLeft(*smallestLetter);
		*smallestLetter = NULL;

		smallestLetter = getMin(heap, size);
		parentalNode->setRight(*smallestLetter);
		*smallestLetter = NULL;


		while (!heap[j % size])
		{
			j++;
		}
		while (heap[j % size]) {
			j++;
		}
		heap[j%size] = parentalNode;

		parentalNode->setLetter(new Letter(' ', parentalNode->getLeft()->getLetter()->getFrequency() + parentalNode->getRight()->getLetter()->getFrequency()));
	}
	this->root = new Node();

	smallestLetter = getMin(heap, size);
	root->setLeft(*smallestLetter);
	*smallestLetter = NULL;

	smallestLetter = getMin(heap, size);
	root->setRight(*smallestLetter);
	*smallestLetter = NULL;

	root->setLetter(new Letter(' ', root->getLeft()->getLetter()->getFrequency() + root->getRight()->getLetter()->getFrequency()));
}

Node** HuffmanTree::getMin(Node** heapArr, int size) {
	Node** ptr1 = heapArr;
	Node** ptr2 = heapArr;

	while (*ptr1 == NULL) {
		ptr1++;
	}
	ptr2 = ptr1;

	while (*ptr2 != NULL && (ptr2 - heapArr) < size) {
		ptr2++;
	}
	if ((ptr2 - heapArr) == size) {
		return ptr1;
	}

	while ((*ptr2 == NULL) && (ptr2 - heapArr) < size){
		ptr2++;
	}
		if ((ptr2 - heapArr) == size) {
		return ptr1;
	}


	if ((*ptr1)->getLetter()->getFrequency() < (*ptr2)->getLetter()->getFrequency()) {
		return ptr1;
	}
	else
	{
		return ptr2;
	}
}

Node* HuffmanTree::getTreeRoot() {
	return this->root;
}

void HuffmanTree::BuildHuffmanTable(Node* node, string code) {
	if (node->getLeft() != NULL) {
		BuildHuffmanTable(node->getLeft(), code + "0");
	}
	if (node->getRight() != NULL) {
		BuildHuffmanTable(node->getRight(), code + "1");
	}
	if (node->getLeft() == NULL && node->getRight() == NULL) {
		this->Table->addCode(node->getLetter()->getCode(), code);
	}
}

CodesTable* HuffmanTree::getTable() {
	return this->Table;
}

Heap HuffmanTree::getHeap() {
	return this->inputHeap;
}