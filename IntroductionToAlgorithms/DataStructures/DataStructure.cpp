#include <iostream>
#include "TestTxtParser.h"
#include "RBTree.h"
#include "BinarySearchTree.h"
#include "Heap.h"
#include <vector>

//void TestBinarySearchTree();
//void TestRBTree();
void TestHeap();

int main()
{
	//TestBinarySearchTree();
	//TestRBTree();
	TestHeap();
}

void TestHeap()
{
	int heapArray[20] = { 4,6,7,1,8,3,4 ,1,2,10,-1 };
	Heap heap(heapArray, 11, 20);
	heap.heapSort();

	heap.HeapDebug();
	heap.IncreaseKey(10, 11);
	heap.HeapDebug();
	heap.Insert(99);
	heap.Insert(-3);
	heap.Insert(-2);
	heap.Insert(0);
	heap.HeapDebug();

	while (!heap.IsEmpty())
	{
		cout << "Max is " << heap.ExtractMaximum() << endl;
	}
}


void TestBinarySearchTree()
{
	BinarySearchTree bsTree;
	bsTree.Insert(5);
	bsTree.Insert(3);
	bsTree.Insert(8);
	bsTree.Insert(7);
	bsTree.InorderWalk(bsTree.root);
	cout << "Successor is " << bsTree.Successor(5)->value << endl;
	cout << "Predecessor is " << bsTree.Predecessor(5)->value << endl;

}

void TestRBTree()
{
	string content = ReadTestTxt();
	vector<string> commandList;
	vector<int> valueList;
	ParserTestContent(content, commandList, valueList);

	RBTree rbTree;
	for (int i = 0; i < commandList.size(); i++)
	{
		string command = commandList[i];
		int value = valueList[i];
		if (command == "insert")
			rbTree.Insert(value);
		if (command == "delete")
		{
			rbTree.Delete(value);
		}
		if (command == "search")
		{
			RBTreeNode* node = rbTree.Search(value);
			string result = node == rbTree.nullNode ? "not found" : "found";
			cout << "searching for " << value << " - " << result << endl;
		}

		string rbTreeCheck = rbTree.CheckRB() ? "Is RBTree" : "Is not RBTree";
		cout << rbTreeCheck << endl;
	}
}