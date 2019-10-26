#pragma once
#include <iostream>

using namespace std;

struct Node
{
	int value;
	Node* next;
	Node* prev;
};

class List
{
public:
	List()
	{
		head = nullptr;
	}
	~List()
	{

	}

	void Insert(int value)
	{
		Node* node = (Node*)malloc(sizeof(Node));
		node->value = value;

		node->next = head;
		node->prev = nullptr;
		if (head != nullptr)
			head->prev = node;

		head = node;
	}

	void Delete(int value)
	{
		Node* toDelete = Search(value);
		if (toDelete == nullptr)
			return;

		if (toDelete->prev != nullptr)
			toDelete->prev->next = toDelete->next;
		else
			head = toDelete->next;

		if (toDelete->next != nullptr)
			toDelete->next->prev = toDelete->prev;

		free(toDelete);
	}

	Node* Search(int value)
	{
		Node* begin = head;
		while (begin != nullptr && begin->next != nullptr && begin->value != value)
		{
			begin = begin->next;
		}

		if (begin->value == value)
		{
			cout << "Find the value " << value << endl;
			return begin;
		}
		else
		{
			return nullptr;
		}
	}

	void Print()
	{
		Node* begin = head;
		while (begin != nullptr)
		{
			cout << "List element value is " << begin->value << endl;
			begin = begin->next;
		}

		cout << "Print is over" << endl;
	}

private:
	Node* head;
};
