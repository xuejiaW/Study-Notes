// DataStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Stack.h"
#include "Queue.h"
//#include "List.h"
#include "List_Sentinels.h"

void testStack();
void testQueue();
void testList();
void testList_Sentinels();

int main()
{
	std::cout << "Hello World!\n";
	testList_Sentinels();
}


void testStack()
{
	Stack s;
	s.push(10);
	s.push(20);
	cout << s.pop() << endl;
	cout << s.pop() << endl;
	cout << s.pop() << endl;
}

void testQueue()
{
	Queue q;
	q.Enqueue(10);
	q.Enqueue(20);
	q.Enqueue(30);

	while (!q.Empty())
		cout << "Queue value is " << q.Dequeue() << endl;

	cout << "Test queue is over" << endl;
}

void testList()
{
	//List l;
	//l.Insert(12);
	//l.Insert(5);
	//l.Insert(4);
	//l.Delete(5);
	//l.Print();
}

void testList_Sentinels()
{
	List_Sentinels ls;
	ls.Insert(12);
	ls.Insert(5);
	ls.Insert(4);
	ls.Insert(3);
	ls.Delete(4);
	ls.Delete(12);
	ls.Print();
}