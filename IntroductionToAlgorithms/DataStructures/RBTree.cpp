#include "RBTree.h";
#include <iostream>;


RBTree::RBTree()
{
	this->nullNode = new RBTreeNode();
	this->rootNode = nullNode;

	this->nullNode->right = this->rootNode;
	this->nullNode->left = this->rootNode;
	this->nullNode->parent = this->rootNode;
	this->nullNode->color = BLACK;

	this->doubleBlackNode = new RBTreeNode();
	this->doubleBlackNode->color = BLACK;
	this->doubleBlackNode->left = nullNode;
	this->doubleBlackNode->right = nullNode;
};


RBTree::~RBTree()
{
	DestroyTree(rootNode);
	delete nullNode;
	delete doubleBlackNode;
}

bool RBTree::CheckRB()
{
	//rule 1 no need to check since every RBTreeNode has color variables
	//rule 3 no need to check since every RBTreeNode has nullNode which color is black as both children

	if (rootNode == nullNode)
		return true;
	if (rootNode->color == RED) //break rule 2
		return false;

	int blackNodesNum_Left = 0;//left path black NodesNum from root
	int blackNodesNum_Right = 0;//left path black NodesNum from root

	RBTreeNode* node = rootNode;
	while (node != nullNode)
	{
		if (node->color == BLACK)
			blackNodesNum_Left++;

		node = node->left;
	}

	node = rootNode;
	while (node != nullNode)
	{
		if (node->color == BLACK)
			blackNodesNum_Right++;

		node = node->right;
	}

	if (blackNodesNum_Left != blackNodesNum_Right)
		return false;


	//Check every node in the tree
	return CheckRB(rootNode, blackNodesNum_Left, 0);
}

bool RBTree::CheckRB(RBTreeNode* node, int rootBlackNodesNum, int currentBlackNodesNum)
{
	if (node == nullNode)
		return true;
	if (node->color == BLACK)
		currentBlackNodesNum++;

	RBTreeNode* parent = node->parent;

	if (parent != nullNode && parent->color == RED && node->color == RED)
		return false; //break rule 4

	if (node == nullNode && currentBlackNodesNum != rootBlackNodesNum)
		return false; //break rule 5


	return CheckRB(node->left, rootBlackNodesNum, currentBlackNodesNum)
		&& CheckRB(node->right, rootBlackNodesNum, currentBlackNodesNum);

}

RBTreeNode* RBTree::Search(int value)
{
	RBTreeNode* node = rootNode;

	while (node != nullNode && node->value != value)
	{
		node = value < node->value ? node->left : node->right;
	}

	return node;
}

bool RBTree::Insert(int value)
{
	RBTreeNode* targetNode = rootNode;
	RBTreeNode* targetNodeParent = nullNode;

	while (targetNode != nullNode)
	{
		targetNodeParent = targetNode;
		if (value < targetNode->value)
		{
			targetNode = targetNode->left;
		}
		else if (value > targetNode->value)
		{
			targetNode = targetNode->right;
		}
		else
		{
			return false;
		}
	}

	RBTreeNode* toInsert = new RBTreeNode();
	toInsert->value = value;
	toInsert->color = RED;
	toInsert->right = nullNode;
	toInsert->left = nullNode;

	if (targetNodeParent == nullNode)//Tree is empty
	{
		rootNode = toInsert;
		rootNode->parent = nullNode;
		nullNode->left = rootNode;
		nullNode->right = rootNode;
		nullNode->parent = rootNode;
	}
	else
	{
		if (value < targetNodeParent->value)
		{
			targetNodeParent->left = toInsert;
		}
		else
		{
			targetNodeParent->right = toInsert;
		}
		toInsert->parent = targetNodeParent;
	}

	InsertFixUp(toInsert);
	return true;
}


void RBTree::InsertFixUp(RBTreeNode* node)
{
	while (node->parent->color == RED)
	{
		if (node->parent == node->parent->parent->left)//The first three cases
		{
			RBTreeNode* uncle = node->parent->parent->right;

			if (uncle->color == RED) //Case 1
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->right) //Case 2
				{
					node = node->parent;
					LeftRotate(node);
				}

				//Case3
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				RightRotate(node->parent->parent);
			}
		}
		else
		{
			//The remainging three cases, as the symmetry of the first three

			RBTreeNode* uncle = node->parent->parent->left;
			if (uncle->color == RED)
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					RightRotate(node);
				}

				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				LeftRotate(node->parent->parent);
			}
		}
	}
	rootNode->color = BLACK;
}


void RBTree::TransPlant(RBTreeNode* originNode, RBTreeNode* newNode)
{
	if (originNode->parent == nullNode)
	{
		rootNode = newNode;
	}
	else if (originNode == originNode->parent->left)
	{
		originNode->parent->left = newNode;
	}
	else
	{
		originNode->parent->right = newNode;
	}

	newNode->parent = originNode->parent;
}

bool RBTree::Delete(int value)
{
	RBTreeNode* toDelete = Search(value);
	if (toDelete == nullNode)
		return false;


	RBTreeNode* toDeleteTrack = toDelete;//this track will be removed from the tree
	NodeColor originDeleteTrackColor = toDeleteTrack->color;

	RBTreeNode* toReplaceTrack;

	if (toDelete->left == nullNode)
	{
		toReplaceTrack = toDelete->right;
		TransPlant(toDelete, toReplaceTrack);
	}
	else if (toDelete->right == nullNode)
	{
		toReplaceTrack = toDelete->left;
		TransPlant(toDelete, toReplaceTrack);
	}
	else //Both children are not nullNode
	{
		toDeleteTrack = GetMinimum(toDelete->right);//The track is Successor
		//This track will moved in toDelete's postion
		originDeleteTrackColor = toDeleteTrack->color;

		toReplaceTrack = toDeleteTrack->right;
		if (toDeleteTrack->parent == toDelete)//Track is toDelete's rightChild
		{
			toReplaceTrack->parent = toDeleteTrack;
		}
		else
		{
			TransPlant(toDeleteTrack, toReplaceTrack);
			toDeleteTrack->right = toDelete->right;
			toDeleteTrack->right->parent = toDeleteTrack;
		}
		TransPlant(toDelete, toDeleteTrack);
		toDeleteTrack->left = toDelete->left;
		toDeleteTrack->left->parent = toDeleteTrack;
		toDeleteTrack->color = toDelete->color;

		//set the pointer be null to ensure children and parent won't be released
		toDelete->parent = nullptr;
		toDelete->right = nullptr;
		toDelete->left = nullptr;
		delete toDelete;
	}
	if (originDeleteTrackColor == BLACK)
	{
		DeleteFixUp(toReplaceTrack);
	}

	return true;
}

void RBTree::DeleteFixUp(RBTreeNode* toReplaceTrack)
{
	while (toReplaceTrack != rootNode && toReplaceTrack->color == BLACK)
	{
		if (toReplaceTrack == toReplaceTrack->parent->left) //The first four cases
		{
			RBTreeNode* uncle = toReplaceTrack->parent->right;
			if (uncle->color == RED)   //case1
			{
				uncle->color = BLACK;
				toReplaceTrack->parent->color = RED;
				LeftRotate(toReplaceTrack->parent);
				uncle = toReplaceTrack->parent->right;   //to case 2/3/4
			}
			if (uncle->left->color == BLACK && uncle->right->color == BLACK)
			{
				uncle->color = RED;    //case2
				toReplaceTrack = toReplaceTrack->parent;
			}
			else
			{
				if (uncle->right->color == BLACK)
				{
					uncle->left->color = BLACK;
					uncle->color = RED;
					RightRotate(uncle);   // to case4
					uncle = toReplaceTrack->parent->right;
				}
				uncle->color = toReplaceTrack->parent->color;
				toReplaceTrack->parent->color = BLACK;          //case4;
				uncle->right->color = BLACK;
				RightRotate(toReplaceTrack->parent);
				toReplaceTrack = rootNode;
			}
		}
		else//The remaining four cases,as the symetry of the first four
		{
			RBTreeNode* uncle = toReplaceTrack->parent->left;
			if (uncle->color == RED)
			{
				uncle->color = BLACK;
				toReplaceTrack->parent->color = RED;
				RightRotate(toReplaceTrack->parent);
				uncle = toReplaceTrack->parent->left;
			}
			if (uncle->right->color == BLACK && uncle->left->color == BLACK)
			{
				uncle->color = RED;
				toReplaceTrack = toReplaceTrack->parent;
			}
			else
			{
				if (uncle->left->color == BLACK)
				{
					uncle->right->color = BLACK;
					uncle->color = RED;
					LeftRotate(uncle);
					uncle = toReplaceTrack->parent->left;
				}
				uncle->color = toReplaceTrack->parent->color;
				toReplaceTrack->parent->color = BLACK;
				uncle->left->color = BLACK;
				RightRotate(toReplaceTrack->parent);
				toReplaceTrack = rootNode;
			}
		}
	}
	toReplaceTrack->color = BLACK;
}


bool RBTree::LeftRotate(RBTreeNode* node)
{
	if (node == nullNode || node->right == nullNode)
	{
		cout << "Invalid operation: LeftRotate";
		return false;
	}

	//lowerRight's left subtree become node's right subtree
	RBTreeNode* lowerRight = node->right;
	node->right = lowerRight->left;
	if (lowerRight->left != nullNode)
	{
		lowerRight->left->parent = node;
	}

	//lowerRight replace node's place
	lowerRight->parent = node->parent;
	if (node->parent == nullNode)
	{
		rootNode = lowerRight;
		nullNode->right = rootNode;
		nullNode->left = rootNode;
		nullNode->parent = rootNode;
	}
	else if (node == node->parent->left)
	{
		node->parent->left = lowerRight;
	}
	else
	{
		node->parent->right = lowerRight;
	}

	//node as lowerRight's left subtree
	node->parent = lowerRight;
	lowerRight->left = node;
}

bool RBTree::RightRotate(RBTreeNode* node)
{
	//As the symmetry of LeftRotate
	if (node == nullNode || node->left == nullNode)
	{
		return false;
	}

	RBTreeNode* lowerLeft = node->left;
	node->left = lowerLeft->right;
	if (lowerLeft->right != nullNode)
	{
		lowerLeft->right->parent = node;
	}

	lowerLeft->parent = node->parent;
	if (node->parent == nullNode)
	{
		rootNode = lowerLeft;
		nullNode->left = rootNode;
		nullNode->right = rootNode;
		nullNode->parent = rootNode;
	}
	else if (node == node->parent->right)
	{
		node->parent->right = lowerLeft;
	}
	else
	{
		node->parent->left = lowerLeft;
	}

	node->parent = lowerLeft;
	lowerLeft->right = node;
}

RBTreeNode* RBTree::GetMinimum(RBTreeNode* node)
{
	if (node->left == nullNode)
		return node;
	return GetMinimum(node->left);
}

void RBTree::InorderTreeWalk(RBTreeNode* node)
{
	if (node == nullNode)
	{
		return;
	}
	else
	{
		InorderTreeWalk(node->left);
		cout << node->value << endl;
		InorderTreeWalk(node->right);
	}
}

void RBTree::DestroyTree(RBTreeNode* node)
{
	if (node == nullNode)
	{
		return;
	}
	else
	{
		DestroyTree(node->left);
		DestroyTree(node->right);
		delete node;
	}
};