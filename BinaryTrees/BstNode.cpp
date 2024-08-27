#include "BstNode.h"

// default constructor
BstNode::BstNode()
{
	this->left = nullptr;
	this->right = nullptr;
	this->list = new LinkedList<int>(); // when a BstNode is created a pointer to a linked list will also be created
}

// constructor with parameter
BstNode::BstNode(std::string data)
{
	this->data = data;
	this->left = nullptr;
	this->right = nullptr;
	this->list = new LinkedList<int>(); // when a BstNode is created a pointer to a linked list will also be created
}