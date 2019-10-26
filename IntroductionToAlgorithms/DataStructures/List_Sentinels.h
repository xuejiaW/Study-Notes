#pragma once

#include <iostream>

using namespace std;

struct Node
{
	int value;
	Node* next;
	Node* prev;
};

class List_Sentinels
{
public:
	List_Sentinels()
	{
		sentials = (Node*)malloc(sizeof(Node));
		sentials->next = sentials;
		sentials->prev = sentials;
	}
	~List_Sentinels()
	{
		free(sentials);
	}

	void Insert(int value)
	{
		Node* node = (Node*)malloc(sizeof(Node));
		node->value = value;

		node->next = sentials->next;
		node->prev = sentials;
		sentials->next->prev = node;
		sentials->next = node;
	}

	void Delete(int value)
	{
		Node* toDelete = Search(value);

		if (toDelete == nullptr)
		{
			cout << "return for value == null" << endl;
			return;
		}

		toDelete->prev->next = toDelete->next;
		toDelete->next->prev = toDelete->prev;

		free(toDelete);
	}

	Node* Search(int value)
	{
		Node* node = sentials->next;
		while (node->value != value && node->next != sentials)
		{
			node = node->next;
		}

		return node->value == value ? node : nullptr;
	}

	void Print()
	{
		Node* node = sentials->next;
		while (node != sentials)
		{
			cout << "value is " << node->value << endl;
			node = node->next;
		}
	}

private:
	Node* sentials;
};
