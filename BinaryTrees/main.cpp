#include "Node.h"
#include "LinkedList.h"
#include "BstNode.h"
#include "BstTree.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

// function signatures
void driver(int argc, char* argv[]);
void printInput(std::ifstream& ifile);
void storeChapter(std::ifstream& ifile, BstTree& tree, BstNode*& root);

int main(int argc, char* argv[])
{
	if (argc < 2) // inform the user on how to use program
	{
		std::cerr << "Standard: " << argv[0] << " NUM_THREADS NUM_TO_TEST" << std::endl;
		std::cerr << "OR..." << std::endl;
		std::cerr << "To Output Prime Numbers To Console: " << argv[0] << " NUM_THREADS NUM_TO_TEST -p" << std::endl;
		std::cerr << "OR..." << std::endl;
		std::cerr << "To Output Prime Numbers To Console: " << argv[0] << " NUM_THREADS NUM_TO_TEST OUTPUT_FILE_PATH" << std::endl;

		return 1;
	}
	else if (argc == 2) // user entered an input file -> log input and output to console
	{
		driver(argc, argv);
	}
	else if (argc > 2) // more than 2 argc's -> output file was specified so log output to console
	{
		driver(argc, argv);
	}

	return 0;
}

void driver(int argc, char* argv[])
{
	// opening the input file
	std::ifstream ifile;
	std::string inPath = argv[1];
	ifile.open(inPath);
	std::ofstream ofile;

	// validation to see if file opened
	if (!ifile.is_open())
	{
		std::cerr << "Invalid input file entered. Please try again!" << std::endl;

		return;
	}

	if (argc > 2)
	{
		std::string outPath = argv[2];
		ofile.open(outPath);

		// validation to see if file opened
		if (!ofile.is_open())
		{
			std::cerr << "Invalid output file entered. Please try again!" << std::endl;

			return;
		}
	}

	if (argc == 2) // user entered an input file -> log input and output to console
	{
		// print the input file to the console then close input file
		printInput(ifile);
		ifile.close();

		// reopen the input file to store information (words and verse appearancess)
		ifile.open(inPath);

		// validation to see if file opened
		if (!ifile.is_open())
		{
			std::cerr << "Invalid input file entered. Please try again!" << std::endl;

			return;
		}
	}

	// create a binary search tree and a root node for this tree
	BstTree tree;
	BstNode* root = nullptr;

	// store the chapter in a binary search tree
	storeChapter(ifile, tree, root);
	ifile.close();

	if (argc == 2)
	{
		// BstTree print function that prints out the words and the verses they were seen on
		tree.printInorder(root, ofile, 2);
	}
	else if (argc > 2)
	{
		// same as above function but when argc == 3 info is printed to the ofile
		tree.printInorder(root, ofile, 3);
		// close the output file
		ofile.close();
	}
}

void printInput(std::ifstream& ifile) // prints the input file to the console char by char
{
	char ch;

	// the last char issue can be fiexed with a double while loop but would be slower
	while (!ifile.eof())
	{
		// read in a character
		ifile >> std::noskipws >> ch;

		if (ifile.eof()) // so last char is only read once
		{
			break;
		}
		// print character to console
		std::cout << ch;
	}
	std::cout << "\n" << std::endl;

	return;
}

void storeChapter(std::ifstream& ifile, BstTree& tree, BstNode*& root) // scripture chapter words are stored in a binary search tree and each time the word
{ // shows up the verse that it appeared in is stored in a linked list (part of binary search tree nodes)
	char ch, number[2], word[12];
	std::string str;
	int verseNum = 0;

	while (!ifile.eof()) // reads until the end of input file is reached
	{
		ifile >> std::noskipws >> ch;

		if (ch >= 48 && ch <= 57) // ch is a digit 0-9
		{
			number[0] = ch;
			ifile >> std::noskipws >> ch;

			if (ch >= 48 && ch <= 57)
			{
				number[1] = ch;
			}

			// set current verse number
			verseNum = atoi(number);
		}
		else if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) // ch is a letter
		{
			int i = 0;
			str = "";

			while ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) // stores ch's until a non-ch is reached
			{
				word[i] = ch;
				ifile >> std::noskipws >> ch;

				if (ch == '\'') // accounts for words ending in 's
				{
					i++;
					word[i] = ch;
					ifile >> std::noskipws >> ch;
				}

				i++;
			}
			// once word is complete
			for (int j = 0; j < i; j++)
			{
				str += word[j];
			}
			// make the word lowercase so no duplicates when there's different punctuation
			std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });

			// search for the word in bst
			BstNode* treeNode = tree.searchNode(root, str);

			if (treeNode == nullptr)
			{
				// insert the word as a node (which yields a new root)
				root = tree.insertBstNode(root, str);

				// research for the node
				treeNode = tree.searchNode(root, str);

				// add the word's associated verseNum to the node's linked list
				treeNode->list->addSorted(verseNum);
			}
			else if (treeNode != nullptr)
			{
				// add the word's associated verseNum to the nodes linked list
				treeNode->list->addSorted(verseNum);
			}
		}
		else
		{
			continue;
		}
	}

	return;
}
