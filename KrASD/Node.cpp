#include "Node.h"

Node::Node()
{
	this->letter = nullptr;
	this->left = nullptr;
	this->right = nullptr;
}

Node::Node(Letter* letter)
{
	this->letter = letter;
	this->left = nullptr;
	this->right = nullptr;
}

Node::Node(Letter* letter, Node* left, Node* right)
{
	this->letter = letter;
	this->left = left;
	this->right = right;
}

Letter* Node::getLetter()
{
	return this->letter;
}

Node* Node::getLeft()
{
	return this->left;
}

Node* Node::getRight()
{
	return this->right;
}

void Node::setLetter(Letter* letter)
{
	this->letter = letter;
}

void Node::setLeft(Node* left)
{
	this->left = left;
}

void Node::setRight(Node* right)
{
	this->right = right;
}


