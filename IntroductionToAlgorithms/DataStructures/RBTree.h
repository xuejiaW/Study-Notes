#pragma once

#include <iostream>
using namespace std;

#include "RBTreeNode.h"

class RBTree
{
private:
	void DestroyTree(RBTreeNode* node);
	bool LeftRotate(RBTreeNode* node);
	bool RightRotate(RBTreeNode* node);
	void InsertFixUp(RBTreeNode* node);
	bool CheckRB(RBTreeNode* root, int blackNodesNum, int k);
	void DeleteFixUp(RBTreeNode* node);
	void TransPlant(RBTreeNode* originNode, RBTreeNode* newNode);

	RBTreeNode* doubleBlackNode;//Used for delete function
public:
	RBTreeNode* rootNode;
	RBTreeNode* nullNode;
	RBTree();
	~RBTree();

	bool CheckRB();
	RBTreeNode* Search(int value);
	bool Insert(int value);
	bool Delete(int value);
	RBTreeNode* GetMinimum(RBTreeNode* node);
	void InorderTreeWalk(RBTreeNode* node);

};