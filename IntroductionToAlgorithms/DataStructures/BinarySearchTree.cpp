#include "BinarySearchTree.h"
#include <iostream>

using namespace std;

void BinarySearchTree::Insert(int value)
{
	BSTreeNode* node = (BSTreeNode*)malloc(sizeof(BSTreeNode));
	node->value = value;
	node->leftChild = nullptr;
	node->rightChild = nullptr;

	BSTreeNode* target = root;
	BSTreeNode* targetParent = nullptr;

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


void BinarySearchTree::InorderWalk(BSTreeNode* rootNode)
{
	if (rootNode == nullptr)
		return;
	InorderWalk(rootNode->leftChild);
	cout << "Node value is " << rootNode->value << endl;
	InorderWalk(rootNode->rightChild);
}

void BinarySearchTree::PreorderWalk(BSTreeNode* rootNode)
{
	if (rootNode == nullptr)
		return;
	cout << "Node value is " << rootNode->value << endl;
	PreorderWalk(rootNode->leftChild);
	PreorderWalk(rootNode->rightChild);
}

void BinarySearchTree::PostorderWalk(BSTreeNode* rootNode)
{
	if (rootNode == nullptr)
		return;
	PostorderWalk(rootNode->leftChild);
	PostorderWalk(rootNode->rightChild);
	cout << "Node value is " << rootNode->value << endl;
}


//BSTreeNode* BinarySearchTree::Search(BSTreeNode* rootNode, int value)
//{
//	if (rootNode == nullptr || rootNode->value == value)
//		return rootNode;
//
//	return value < rootNode->value ? Search(rootNode->leftChild, value) : Search(rootNode->rightChild, value);
//}

BSTreeNode* BinarySearchTree::Search(BSTreeNode* rootNode, int value)
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

BSTreeNode* BinarySearchTree::Maximum(BSTreeNode* node)
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

BSTreeNode* BinarySearchTree::Minimum(BSTreeNode* node)
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

BSTreeNode* BinarySearchTree::Successor(int value)
{
	BSTreeNode* node = Search(root, value);
	if (node == nullptr)
	{
		cout << "Can't find node with " << value << endl;
		return nullptr;
	}

	if (node->rightChild != nullptr)
		return Minimum(node->rightChild);

	BSTreeNode* nodeParent = node->parent;

	while (nodeParent != nullptr && node == nodeParent->rightChild)
	{
		node = nodeParent;
		nodeParent = node->parent;
	}

	return nodeParent;
}

BSTreeNode* BinarySearchTree::Predecessor(int value)
{
	BSTreeNode* node = Search(root, value);
	if (node == nullptr)
	{
		cout << "Can't find node with " << value << endl;
		return nullptr;
	}

	if (node->leftChild != nullptr)
		return Maximum(node->leftChild);

	BSTreeNode* nodeParent = node->parent;

	while (nodeParent != nullptr && node == nodeParent->leftChild)
	{
		node = nodeParent;
		nodeParent = node->parent;
	}

	return nodeParent;
}


void BinarySearchTree::Delete(int value)
{
	BSTreeNode* toDeleteNode = Search(root, value);
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
		BSTreeNode* successorNode = Minimum(toDeleteNode->rightChild);

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

void BinarySearchTree::transplant(BSTreeNode* originNode, BSTreeNode* newNode)
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