#ifndef _BstNode_H
#define _BstNode_H

#include "LinkedList.h"

// linked list node template class
class BstNode
{
public:
	// member variables
	std::string data;
	BstNode* left;
	BstNode* right;
	LinkedList<int>* list; // each bst node points to a linked list

	// default constructor
	BstNode();
	
	// constructor with parameter
	BstNode(std::string data);
};

#endif
