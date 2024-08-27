#include "BstTree.h"

#include <iostream>
#include <fstream>

// default constructor
BstTree::BstTree()
{
	this->root = nullptr;
}

// method definitions
BstNode* BstTree::createBstNode(std::string data) // dynamically creates a new bst node on the heap and returns it to be inserted in the binary search tree
{
	BstNode* node = new BstNode();
	node->data = data;
	node->left = nullptr;
	node->right = nullptr;

	return node;
}

BstNode* BstTree::insertBstNode(BstNode* root, std::string data) // inserts a bst node in the right spot
{
	if (root == nullptr)
	{
		root = createBstNode(data);

		return root;
	}
	else if (data <= root->data)
	{
		root->left = insertBstNode(root->left, data);
	}
	else
	{
		root->right = insertBstNode(root->right, data);
	}

	return root;
}

BstNode* BstTree::searchNode(BstNode* root, std::string data) // searches for a bst node with the data value equal to the data passed in and returns the node for editing, etc.
{
	while (root != nullptr)
	{
		if (data == root->data)
		{
			return root;
		}
		else if (data < root->data)
		{
			root = root->left;
		}
		else if (data > root->data)
		{
			root = root->right;
		}
	}
	return nullptr;
}

void BstTree::printInorder(BstNode* root, std::ofstream& ofile, int argc) // prints out the binary search tree in alphabetical order and each node's linked list
{
	if (root == NULL)
		return;

	/* first recur on left child */
	printInorder(root->left, ofile, argc);

	if (argc == 2)
	{
		// then print the data of node to console
		std::cout << root->data << ": ";
		root->list->printList(ofile, argc);
	}
	else if (argc == 3)
	{
		ofile << root->data << ": ";
		root->list->printList(ofile, argc);
	}

	/* now recur on right child */
	printInorder(root->right, ofile, argc);
}