#include "Heap.h"

Heap::Heap(){}

Heap::Heap(char* filename)
{
	table.generateTable(filename);
	calculateSize(table);
	readTable(table);
	HeapSort(heap, size);
}

Heap::Heap(unsigned int* frequencies)
{
	table.setTable(frequencies);
	calculateSize(table);
	readTable(table);
	HeapSort(heap, size);
}

// calculates size of heap
void Heap::calculateSize(FrequencyTable table)
{
	unsigned int* frequencies = table.getTable();

	for (int i = 0; i < 256; i++) {
		if (*(frequencies + i)) {
			this->size++;
		}
	}
}

// initialization of letter array, which is used to build heap
void Heap::readTable(FrequencyTable table)
{
	unsigned int * frequencies = table.getTable();
	heap = new Node * [size];

	int j = 0;
	for (int i = 0; i < 256; i++) {
		if (*(frequencies + i)) {
			*(heap + j) = new Node(new Letter(i, *(frequencies + i)));
			j++;
		}
	}
}

void Heap::Swap(Node*& a, Node*& b)
{
	Node* temp = a;
	a = b;
	b = temp;
}

// Heap sort function
void Heap::HeapSort(Node** arr, int N)
{
	for (int i = N / 2 - 1; i >= 0; i--)
		Heapify(arr, N, i);

	for (int i = N - 1; i > 0; i--)
	{
		Swap(arr[0], arr[i]);
		Heapify(arr, i, 0);
	}
}

void Heap::Heapify(Node** arr, int N, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	if (l < N && arr[l]->getLetter()->getFrequency() > arr[largest]->getLetter()->getFrequency())
		largest = l;

	if (r < N && arr[r]->getLetter()->getFrequency() > arr[largest]->getLetter()->getFrequency())
		largest = r;

	if (largest != i)
	{
		Swap(arr[i], arr[largest]);
		Heapify(arr, N, largest);
	}
}


int Heap::getSize()
{
	return size;
}

Node** Heap::getHeap()
{
	return heap;
}


unsigned int* Heap::getFrequencies()
{
	return table.getTable();
}
