#pragma once
#include <iostream>

#define QUEUESIZE 3

using namespace std;


class Queue
{
public:
	Queue()
	{
		head = tail = 0;
	}
	~Queue()
	{
		head = tail = 0;
	}

	bool Enqueue(int value)
	{
		if ((tail + 1) % QUEUESIZE == 0)
		{
			cout << "Queue is full" << endl;
			return false;
		}

		data[tail] = value;

		tail = (tail == QUEUESIZE - 1) ? 0 : tail + 1;

		return true;
	}

	int Dequeue()
	{
		if (Empty())
		{
			cout << "Queue is empty" << endl;
			return -1;
		}

		int value = data[head];

		head = (head == QUEUESIZE - 1) ? 0 : head + 1;

		return value;
	}

	bool Empty()
	{
		return head == tail;
	}

private:
	int data[QUEUESIZE];
	int head;
	int tail;
};

