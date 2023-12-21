#include "ShenonFanoAlgorithm.h"

ShenonFanoAlgorithm::ShenonFanoAlgorithm() {}

ShenonFanoAlgorithm::ShenonFanoAlgorithm(char* filename) {
	this->inputHeap = *(new Heap(filename));
    this->table = new CodesTable();
	BuildShenonFanoTable();
}

ShenonFanoAlgorithm::ShenonFanoAlgorithm(unsigned int* frequencies) {
	this->inputHeap = *(new Heap(frequencies));
    this->table = new CodesTable();
	BuildShenonFanoTable();
}

void ShenonFanoAlgorithm::BuildShenonFanoTable() {
    Node** heap = this->inputHeap.getHeap();
    CalculateCodeRecursive("", heap, heap + this->inputHeap.getSize() - 1);
}

void ShenonFanoAlgorithm::CalculateCodeRecursive(std::string code, Node** start, Node** end) {
    if (end == start) {
        this->table->addCode((*start)->getLetter()->getCode(), code);
        return;
    }

    Node** mid = this->getMid(start, end);
    this->CalculateCodeRecursive(code + "0", start, mid);
    this->CalculateCodeRecursive(code + "1", mid + 1, end);
}

Node** ShenonFanoAlgorithm::getMid(Node** start, Node** end) {
    unsigned int sum_left = 0;
    unsigned int sum_right = 0;
    for (Node** i = start; i <= end; i++) {
        sum_right += (*i)->getLetter()->getFrequency();
    }

    for (Node** mid = start; mid <= end; mid++) {
        if (sum_left > sum_right) {
            return mid - 1;
        }
        sum_left += (*mid)->getLetter()->getFrequency();
        sum_right -= (*mid)->getLetter()->getFrequency();
    }
    return end - 1;
}

unsigned int* ShenonFanoAlgorithm::getFrequencies() {
    return this->inputHeap.getFrequencies();
}

CodesTable* ShenonFanoAlgorithm::getCodesTable() {
    return this->table;
}
