#pragma once

#include <iostream>
using namespace std;

enum NodeColor
{
	RED,
	BLACK
};


class RBTreeNode
{
public:
	RBTreeNode()
	{
		right = NULL;
		left = NULL;
		parent = NULL;
	}
	~RBTreeNode() {}

	int value;
	RBTreeNode* right;
	RBTreeNode* left;
	RBTreeNode* parent;
	NodeColor color;
};
