#include <iostream>
#include "TestTxtParser.h"
#include "RBTree.h"
#include "BinarySearchTree.h"
#include <vector>

void TestBinarySearchTree();
void TestRBTree();


int main()
{
	TestBinarySearchTree();
}

void TestBinarySearchTree()
{
	BinarySearchTree bsTree;
	bsTree.Insert(5);
	bsTree.Insert(3);
	bsTree.Insert(8);
	bsTree.Insert(7);
	bsTree.InorderWalk(bsTree.root);

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

		//string rbTreeCheck = rbTree.CheckRB() ? "Is RBTree" : "Is not RBTree";
		//cout << rbTreeCheck << endl;
	}
}