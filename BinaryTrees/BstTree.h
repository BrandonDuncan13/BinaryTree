#ifndef _BstTree_H
#define _BstTree_H

#include "BstNode.h"

// binary search tree template class
class BstTree
{
public:
	// member variables
	BstNode* root;

	// default constructor
	BstTree();

	// method definitions
	BstNode* createBstNode(std::string data);
	// don't think this method would have to return a bst node if I used loops instead of recursion
	BstNode* insertBstNode(BstNode* root, std::string data);
	BstNode* searchNode(BstNode* root, std::string data);
	void printInorder(BstNode* root, std::ofstream& ofile, int argc);
};

#endif