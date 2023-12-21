#pragma once
#include "Letter.h"

class Node
{
public:
	Node(Letter* letter, Node* left, Node* right);
	Node(Letter* letter);
	Node();
	Letter* getLetter();
	Node* getLeft();
	Node* getRight();
	void setLetter(Letter* letter);
	void setLeft(Node* left);
	void setRight(Node* right);
private:
	Letter* letter;
	Node* left;
	Node* right;
};

