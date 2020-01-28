#pragma once

#include <iostream>
#include "Node.h"
using namespace std;

template <class T>
class Wheels
{
public:

	Wheels()
	{
		head = nullptr;
	}

	~Wheels()
	{
		emptyW();
	}

	bool isEmptyW()
	{
		return head == nullptr;
	}

	void rightW()
	{
		if (isEmptyW())
			cout << "Illegal operation";
		else
			head = head->next;
	}


	void leftW()
	{
		if (isEmptyW())
			cout << "Illegal operation";
		else
			head = head->prev;
	}


	Node<T>* headW()
	{
		return head;
	}


	void emptyW()
	{
		//Delete all elements in the wheels
		if (head == nullptr)
			return;

		Node<T>* node = extractW();
		while (node != nullptr)
		{
			delete(node);
			node = extractW();
		}
		head = nullptr;
	}


	Node<T>* InsertW(T value)
	{
		Node<T>* node = new Node<T>(value);
		return InsertW(node);
	}

	Node<T>* InsertW(Node<T>* node)
	{
		if (isEmptyW())
		{
			head = node;
			head->prev = node;
			head->next = node;
		}
		else
		{
			node->next = head;
			node->prev = head->prev;
			head->prev->next = node;
			head->prev = node;
			head = node;
		}

		return node;
	}

	Node<T>* extractW()
	{
		Node<T>* extracted = head;

		if (isEmptyW() || head->prev == head)//only one element
		{
			head = nullptr;
		}
		else
		{
			head->prev->next = head->next;
			head->next->prev = head->prev;
			rightW();//head = head->next
		}
		return extracted;
	}

	Node<T>* deleteW(Node<T>* toDelete)
	{
		//No check for whether is in the list
		if (toDelete == head)
			return extractW();

		toDelete->next->prev = toDelete->prev;
		toDelete->prev->next = toDelete->next;

		return toDelete;
	}

private:
	Node<T>* head;
};
