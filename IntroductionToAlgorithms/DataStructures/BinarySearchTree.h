#pragma once

#include <iostream>
#include "BSTreeNode.h"
using namespace std;



class BinarySearchTree
{
public:
	BSTreeNode* root;

	BinarySearchTree();
	~BinarySearchTree();
	void Insert(int value);
	void Delete(int value);
	void InorderWalk(BSTreeNode* rootNode);
	void PreorderWalk(BSTreeNode* rootNode);
	void PostorderWalk(BSTreeNode* rootNode);
	BSTreeNode* Search(BSTreeNode* rootNode, int value);
	BSTreeNode* Minimum(BSTreeNode* node);
	BSTreeNode* Maximum(BSTreeNode* node);
	BSTreeNode* Successor(int value);
	BSTreeNode* Predecessor(int value);

private:
	void transplant(BSTreeNode* originNode, BSTreeNode* newNode);
};

