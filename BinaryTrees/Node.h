#ifndef _Node_H
#define _Node_H

// linked list node template class
template <class T> class Node
{
public:
	// member variables
	T data;
	Node<T>* next;

	// default constructor
	Node<T>()
	{
		this->next = nullptr;
	}

	// constructor with parameter
	Node<T>(T data)
	{
		this->data = data;
		this->next = nullptr;
	}
};

#endif