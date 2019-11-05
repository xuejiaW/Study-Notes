#pragma once

#include <iostream>
using namespace std;

struct TreeNode
{
	int value;
	TreeNode* parent;
	TreeNode* leftChild;
	TreeNode* rightChild;
};

class BinarySearchTree
{
public:
	TreeNode* root;

	BinarySearchTree();
	~BinarySearchTree();
	void Insert(int value);
	void Delete(int value);
	void InorderWalk(TreeNode* rootNode);
	void PreorderWalk(TreeNode* rootNode);
	void PostorderWalk(TreeNode* rootNode);
	TreeNode* Search(TreeNode* rootNode, int value);
	TreeNode* Minimum(TreeNode* node);
	TreeNode* Maximum(TreeNode* node);

private:
	void transplant(TreeNode* originNode, TreeNode* newNode);
};

void BinarySearchTree::Insert(int value)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	node->value = value;
	node->leftChild = nullptr;
	node->rightChild = nullptr;

	TreeNode* target = root;
	TreeNode* targetParent = nullptr;

	while (target != nullptr)
	{
		targetParent = target;
		target = value < target->value ? target->leftChild : target->rightChild;
	}

	if (targetParent == nullptr)
	{
		root = node;
		return;
	}

	if (value < targetParent->value)
		targetParent->leftChild = node;
	else
		targetParent->rightChild = node;

	node->parent = targetParent;
}


void BinarySearchTree::InorderWalk(TreeNode* rootNode)
{
	if (rootNode == nullptr)
		return;
	InorderWalk(rootNode->leftChild);
	cout << "Node value is " << rootNode->value << endl;
	InorderWalk(rootNode->rightChild);
}

void BinarySearchTree::PreorderWalk(TreeNode* rootNode)
{
	if (rootNode == nullptr)
		return;
	cout << "Node value is " << rootNode->value << endl;
	PreorderWalk(rootNode->leftChild);
	PreorderWalk(rootNode->rightChild);
}

void BinarySearchTree::PostorderWalk(TreeNode* rootNode)
{
	if (rootNode == nullptr)
		return;
	PostorderWalk(rootNode->leftChild);
	PostorderWalk(rootNode->rightChild);
	cout << "Node value is " << rootNode->value << endl;
}


//TreeNode* BinarySearchTree::Search(TreeNode* rootNode, int value)
//{
//	if (rootNode == nullptr || rootNode->value == value)
//		return rootNode;
//
//	return value < rootNode->value ? Search(rootNode->leftChild, value) : Search(rootNode->rightChild, value);
//}

TreeNode* BinarySearchTree::Search(TreeNode* rootNode, int value)
{
	while (rootNode != nullptr && rootNode->value != value)
	{
		if (value < rootNode->value)
			rootNode = rootNode->leftChild;
		else
			rootNode = rootNode->rightChild;
	}

	return rootNode;
}

TreeNode* BinarySearchTree::Maximum(TreeNode* node)
{
	if (node == nullptr)
	{
		cout << "Tree is empty";
		return nullptr;
	}
	while (node->rightChild != nullptr)
	{
		node = node->rightChild;
	}

	return node;
}

TreeNode* BinarySearchTree::Minimum(TreeNode* node)
{
	if (node == nullptr)
	{
		cout << "Tree is empty";
		return nullptr;
	}
	while (node->leftChild != nullptr)
	{
		node = node->leftChild;
	}

	return node;
}

void BinarySearchTree::Delete(int value)
{
	TreeNode* toDeleteNode = Search(root, value);
	if (toDeleteNode == nullptr)
	{
		//cout << "There is no node with value " << value << endl;
		return;
	}

	if (toDeleteNode->leftChild == nullptr)
		transplant(toDeleteNode, toDeleteNode->rightChild);
	else if (toDeleteNode->rightChild == nullptr)
		transplant(toDeleteNode, toDeleteNode->leftChild);
	else
	{
		TreeNode* successorNode = Minimum(toDeleteNode->rightChild);

		if (successorNode->parent != toDeleteNode)
		{
			transplant(successorNode, successorNode->rightChild);
			//Handle toDeleteNode's right child
			//因为successorNode不是toDelete的子节点，所以toDeleteNode的右节点一定比他大，所以作为它的右子树。
			successorNode->rightChild = toDeleteNode->rightChild;
			toDeleteNode->rightChild->parent = successorNode;
		}

		transplant(toDeleteNode, successorNode);
		//Handle toDeleteNode's left child
		successorNode->leftChild = toDeleteNode->leftChild;
		toDeleteNode->leftChild->parent = successorNode;

		free(toDeleteNode);
	}

}

void BinarySearchTree::transplant(TreeNode* originNode, TreeNode* newNode)
{
	if (originNode->parent == nullptr)
		root = newNode;
	else if (originNode == originNode->parent->leftChild)
		originNode->parent->leftChild = newNode;
	else
		originNode->parent->rightChild = newNode;

	if (newNode != nullptr)
		newNode->parent = originNode->parent;
}

BinarySearchTree::BinarySearchTree()
{
}

BinarySearchTree::~BinarySearchTree()
{
}