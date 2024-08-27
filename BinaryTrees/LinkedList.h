#ifndef _LinkedList_H
#define _LinkedList_H

#include "Node.h"

#include <iostream>
#include <fstream>

// single linked list template class
template <class T> class LinkedList
{
public:
	// member variables
	Node<T>* head;
	Node<T>* sorted;

	// default constructor
	LinkedList<T>() // linked list has no nodes to start
	{
		this->head = nullptr;
		this->sorted = nullptr;
	}

	// method definitions
	Node<T>* findNode(T data) // pass in a data value to find that value within the linked list
	{
		Node<T>* current = head;

		if (current == nullptr)
		{
			return nullptr; // a position variable will be set to the return value
		}

		while (current != nullptr)
		{
			if (current->data == data)
			{
				return current;
			}
			current = current->next;
		}
		// if the data value is not found then nullptr is returned
		return nullptr;
	}

	void addSorted(T data) // a new node is added to the linked list in the correct position for an ascending order list
	{
		// create a new node
		Node<T>* node = new Node<T>(data); // here m_dll is set to point to NULL

		// add a node when the list is empty
		if (head == nullptr)
		{
			head = node;

			return;
		}

		Node<T>* current = head;
		// traversing through the linked list
		while (current->next != nullptr)
		{
			// update current
			current = current->next;
		}
		// now you should be at the end of the linked list
		// the new node is added to the end of the list and it's next is already pointing to NULL
		current->next = node;
	}

	void deleteNode(int position) // position is the position of the node in the linked list
	{
		Node<T>* current = head;

		if (position == -1)
		{
			std::cout << "Cannot delete node because the list is empty or the node wasn't found." << std::endl;
			return;
		}
		else if (position == 0)
		{
			// when we want to delete the head node we move the head to next node
			head = current->next;
			delete current;
			return;
		}
		else
		{
			// getting temp to point at the position 1 less than the desired
			for (int i = 0; i <= (position - 1); i++)
			{
				current = current->next;
			}

			Node<T>* d = current->next; // desired node

			// node before the node being deleted will now point to the node after the node being deleted
			// temp1's next will point to NULL if d's next points to NULL
			current->next = d->next;
			// deletes node d
			delete d;
		}
	}

	void printList(std::ofstream& ofile, int argc) // prints out each node of the linked list seperated by ,'s
	{
		Node<T>* current = head;

		while (current != nullptr)
		{
			if (current->next != nullptr)
			{
				if (argc == 2)
				{
					std::cout << current->data << ",";
				}
				else if (argc == 3)
				{
					ofile << current->data << ",";
				}
			}
			else if (current->next == nullptr)
			{
				if (argc == 2)
				{
					std::cout << current->data << std::endl;
				}
				else if (argc == 3)
				{
					ofile << current->data << std::endl;
				}
			}

			current = current->next;
		}
	}
};

#endif