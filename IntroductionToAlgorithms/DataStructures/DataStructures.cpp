// DataStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Stack.h"
#include "Queue.h"
//#include "List.h"
#include "List_Sentinels.h"
#include "BinarySearchTree.h"
#include "TestTxtParser.h"
#include "RBTree.h"
#include <vector>

void testStack();
void testQueue();
void testList();
void testList_Sentinels();
void testBinarySearchTree();
void TestRBTreeWithTestFile();

int main()
{
	TestRBTreeWithTestFile();
}

void TestRBTreeWithTestFile()
{
	RB_Tree bst;

	string content = ReadTestTxt();
	vector<string> commandList;
	vector<int> valueList;
	ParserTestContent(content, commandList, valueList);
	for (int i = 0; i < commandList.size(); i++)
	{
		string command = commandList[i];
		int value = valueList[i];
		if (command == "insert")
			bst.Insert(value);
		if (command == "delete")
		{
			bst.Delete(value);
		}
		if (command == "search")
		{
			RB_Node* node = bst.find(value);
			string result = node == bst.nullNode ? "not found" : "found";
			cout << "searching for " << value << " - " << result << endl;
		}
	}
	//bst.InOrderTraverse();

}

void TestBinarySearchTreeWithTestFile()
{
	BinarySearchTree bst;

	string content = ReadTestTxt();
	vector<string> commandList;
	vector<int> valueList;
	ParserTestContent(content, commandList, valueList);
	for (int i = 0; i < commandList.size(); i++)
	{
		string command = commandList[i];
		int value = valueList[i];
		if (command == "insert")
			bst.Insert(value);
		if (command == "delete")
		{
			bst.Delete(value);
		}
		if (command == "search")
		{
			TreeNode* node = bst.Search(bst.root, value);
			string result = node == nullptr ? "not found" : "found";
			cout << "searching for " << value << " - " << result << endl;
		}
	}
}


void testBinarySearchTree()
{
	BinarySearchTree bst;
	bst.Insert(5);
	bst.Insert(10);
	bst.Insert(3);
	bst.Insert(7);
	bst.Insert(20);
	cout << "Inorder is :" << endl;
	bst.InorderWalk(bst.root);
	cout << endl << "Preorder is :" << endl;
	bst.PreorderWalk(bst.root);
	cout << endl << "Postorder is :" << endl;
	bst.PostorderWalk(bst.root);

	TreeNode* maxNode = bst.Maximum(bst.root);
	TreeNode* minNode = bst.Minimum(bst.root);

	if (maxNode != nullptr)
		cout << endl << "max value is " << maxNode->value << endl;
	if (minNode != nullptr)
		cout << endl << "min value is " << minNode->value << endl;


	bst.Delete(3);
	bst.Delete(10);
	cout << endl << "Inorder after delete is :" << endl;
	bst.InorderWalk(bst.root);

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