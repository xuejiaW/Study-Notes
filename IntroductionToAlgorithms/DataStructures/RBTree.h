#include <iostream>

using namespace std;

enum NodeColor
{
	RED,
	BLACK
};


class RB_Node   //结点类
{
public:
	RB_Node()   //节点类构造
	{
		right = NULL;
		left = NULL;
		parent = NULL;
	}
	NodeColor color; //颜色
	RB_Node* right;  //右子树
	RB_Node* left;   //左子树
	RB_Node* parent; //父结点
	int value;    //键
};


class RB_Tree
{
private:
	RB_Tree(const RB_Tree& input) {}
	const RB_Tree& operator=(const RB_Tree& input) {}
	void InOrderTraverse(RB_Node* node); //中序遍历
	void clear(RB_Node* node);   //清除RB树
	RB_Node* doubleBlackNode;
public:
	RB_Node* root;
	RB_Node* nullNode;
	RB_Tree();  //构造函数
	bool Empty();   //是否为空树
	RB_Node* find(int key);  //查找键key的值
	bool Insert(int key);    //插入
	void InsertFixUp(RB_Node* node); //插入后修复
	bool RotateLeft(RB_Node* node);      //左旋
	bool RotateRight(RB_Node* node); //右旋
	bool Delete(int key);   //删除
	void DoubleBlackFixUp(RB_Node* node);    //双黑修复
	RB_Node* FindMin(RB_Node* node);
	void InOrderTraverse()  //中序遍历外部接口
	{
		InOrderTraverse(root);
	}
	~RB_Tree()
	{
		clear(root);
		delete nullNode;
	}
};

RB_Tree::RB_Tree()       //构造函数
{
	this->nullNode = new RB_Node();
	this->root = nullNode;
	this->nullNode->right = this->root;
	this->nullNode->left = this->root;
	this->nullNode->parent = this->root;
	this->nullNode->color = BLACK;

	this->doubleBlackNode = new RB_Node();
	this->doubleBlackNode->color = BLACK;
	this->doubleBlackNode->left = nullNode;
	this->doubleBlackNode->right = nullNode;
};


bool RB_Tree::Empty()
{
	if (this->root == this->nullNode)
	{
		return true;
	}
	else
	{
		return false;
	}
}


RB_Node* RB_Tree::find(int key)   //查找，此处可递归，参考上一篇二叉查找树
{
	RB_Node* index = root;
	while (index != nullNode)
	{
		if (key < index->value)
		{
			index = index->left;
		}
		else if (key > index->value)
		{
			index = index->right;
		}
		else
		{
			break;
		}
	}
	return index;
}

/*
	左旋，构造一个指针lower_right指向旋转点的右孩子。
	lower_right的父结点为旋转点的父结点,旋转点的右孩子为lower_right的左孩子（如果左孩子不为空，则还要设置左孩子的父亲为旋转点）。
	判断旋转点是否为根节点。是的话更改m_root的值，否则更改旋转点的父结点左孩子 or 右孩子的指向。
	更改旋转点父结点为lower_right，lower_right的左孩子为旋转点
*/
bool RB_Tree::RotateLeft(RB_Node* node)
{
	if (node == nullNode || node->right == nullNode)
	{
		return false;   //不能旋转
	}
	RB_Node* lower_right = node->right;
	lower_right->parent = node->parent;
	node->right = lower_right->left;
	if (lower_right->left != nullNode)
	{
		lower_right->left->parent = node;
	}
	if (node->parent == nullNode)
	{
		root = lower_right;
		nullNode->right = root;
		nullNode->left = root;
		nullNode->parent = root;
	}
	else
	{
		if (node == node->parent->left)
		{
			node->parent->left = lower_right;
		}
		else
		{
			node->parent->right = lower_right;
		}
	}
	node->parent = lower_right;
	lower_right->left = node;
}

bool RB_Tree::RotateRight(RB_Node* node)  //右旋，原理同左旋,left和right交换就可以
{
	if (node == nullNode || node->left == nullNode)
	{
		return false;//can't rotate    
	}
	RB_Node* lower_left = node->left;
	node->left = lower_left->right;
	lower_left->parent = node->parent;
	if (lower_left->right != nullNode)
	{
		lower_left->right->parent = node;
	}
	if (node->parent == nullNode) //node is root    
	{
		root = lower_left;
		nullNode->left = root;
		nullNode->right = root;
		nullNode->parent = root;    
	}
	else
	{
		if (node == node->parent->right)
		{
			node->parent->right = lower_left;
		}
		else
		{
			node->parent->left = lower_left;
		}
	}
	node->parent = lower_left;
	lower_left->right = node;
}

/*
		插入，while循环将insert_point指向要插入的点
		如果插入点已经存在，返回false，如果插入的是一颗空树，直接赋值给根节点。否则在插入点赋值
*/
bool RB_Tree::Insert(int key)
{
	RB_Node* targetNode = root;
	RB_Node* targetNodeParent = nullNode;

	while (targetNode != nullNode)
	{
		targetNodeParent = targetNode;
		if (key < targetNode->value)
		{
			targetNode = targetNode->left;
		}
		else if (key > targetNode->value)
		{
			targetNode = targetNode->right;
		}
		else
		{
			return false;
		}
	}   //此时insert_point指向要插入的点
	RB_Node* insert_node = new RB_Node(); //构造插入的结点
	insert_node->value = key;
	insert_node->color = RED;
	insert_node->right = nullNode;
	insert_node->left = nullNode;
	if (targetNodeParent == nullNode)        //如果是一颗空树
	{
		root = insert_node;
		root->parent = nullNode;
		nullNode->left = root;
		nullNode->right = root;
		nullNode->parent = root;
	}
	else
	{
		if (key < targetNodeParent->value)
		{
			targetNodeParent->left = insert_node;
		}
		else
		{
			targetNodeParent->right = insert_node;
		}
		insert_node->parent = targetNodeParent;
	}
	InsertFixUp(insert_node);   //调用InsertFixUp修复红黑树性质
}

/*
A   父亲节点为红色时才修复
	插入修复：分为插入点的父结点是祖父结点的左孩子还是右孩子
B   左孩子的话：
 C      创建一个uncle结点指向叔叔节点（父结点的兄弟）。
 D      1）如果叔叔结点为红色：父结点和叔叔结点变黑，祖父节点变红且作为当前结点
 E      2）叔叔节点为黑色：如果插入节点是父节点的右孩子：父结点作为当前节点然后左旋，转换为情况三继续处理
 F      3）叔叔节点为黑色：插入节点为左孩子：父结点变黑，祖父变红，祖父结点为支点右旋
G   右孩子的话：
*/
void RB_Tree::InsertFixUp(RB_Node* node)
{
	while (node->parent->color == RED)        //A
	{
		if (node->parent == node->parent->parent->left)    //B
		{
			RB_Node* uncle = node->parent->parent->right;   //C
			if (uncle->color == RED) //D
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else if (uncle->color == BLACK)
			{
				if (node == node->parent->right) //E
				{
					node = node->parent;
					RotateLeft(node);
				}
				//F
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				RotateRight(node->parent->parent);
			}
		}
		else    //G
		{
			RB_Node* uncle = node->parent->parent->left;
			if (uncle->color == RED)
			{
				node->parent->color = BLACK;
				uncle->color = BLACK;
				uncle->parent->color = RED;
				node = node->parent->parent;
			}
			else if (uncle->color == BLACK)
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					RotateRight(node);
				}

				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				RotateLeft(node->parent->parent);
			}
		}
	}
	root->color = BLACK;    //修复根节点颜色，防止被改为红色
}

/*
	删除一个结点：

*/
bool RB_Tree::Delete(int key)
{

	RB_Node* delete_point = find(key);   //找到要删除的点
	if (delete_point == nullNode)
	{
		return false;
	}
	if (delete_point->left != nullNode && delete_point->right != nullNode) //有两个子结点
	{
		RB_Node* replace_node = FindMin(delete_point->right);
		//删除点和替换点的值互换，结点颜色不换
		int tmpkey = delete_point->value;
		delete_point->value = replace_node->value;
		replace_node->value = tmpkey;
		delete_point = replace_node;
	}
	RB_Node* delete_point_child;
	if (delete_point->color == RED)  //若该节点为红色
	{
		if (delete_point == delete_point->parent->left)   //如果是左孩子
		{
			delete_point->parent->left = nullNode;
		}
		else   //如果是右孩子
		{
			delete_point->parent->right = nullNode;
		}
		delete delete_point;
	}

	else if (delete_point->right != nullNode) //如果右结点不为空,此时要删除的结点肯定为黑色，且右结点肯定为红色
	{
		if (delete_point == delete_point->parent->left)  //要删除的点是左结点
		{
			delete_point->parent->left = delete_point->right;
			delete_point->right->parent = delete_point->parent;
		}
		else
		{
			delete_point->parent->right = delete_point->right;
			delete_point->right->parent = delete_point->parent;
		}
		delete_point->right->color = BLACK;    //右结点颜色改为黑色
		delete delete_point;
	}
	else if (delete_point->left != nullNode)  //如果左结点不为空（未经过替换），与右节点不为空操作一样
	{
		if (delete_point == delete_point->parent->left)   //要删除的点是左结点
		{
			delete_point->parent->left = delete_point->left;
			delete_point->left->parent = delete_point->parent;
		}
		else
		{
			delete_point->parent->right = delete_point->left;
			delete_point->left->parent = delete_point->parent;
		}
		delete_point->left->color = BLACK; //右结点颜色改为黑色
		delete delete_point;
	}
	else    //无子节点的情况
	{
		//此时唯一剩下情况为，要删除结点为黑色且无子结点
		if (delete_point->parent == nullNode)  //如果要删除的是根节点
		{
			root = nullNode;
			nullNode->parent = root;
			nullNode->left = root;
			nullNode->left = root;
			delete delete_point;
		}
		else
		{


			RB_Node* tmp = delete_point->parent;
			if (delete_point == delete_point->parent->left)   //如果要删除结点为左节点
			{

				delete delete_point;
				tmp->left = doubleBlackNode;
				doubleBlackNode->parent = tmp;
				DoubleBlackFixUp(doubleBlackNode);
				tmp->left = nullNode;
			}
			else    //如果要删除结点为右节点
			{

				delete delete_point;
				tmp->right = doubleBlackNode;
				doubleBlackNode->parent = tmp;
				DoubleBlackFixUp(doubleBlackNode);
				tmp->right = nullNode;
			}
		}
	}
}

/*
	双黑修复
*/
void RB_Tree::DoubleBlackFixUp(RB_Node* node) //传过来的参数都是双黑结点
{

	if (node == node->parent->left)  //如果此结点是左结点
	{

		RB_Node* brother = node->parent->right;
		//情况3
		if (brother->color == RED)
		{
			node->parent->color = RED;
			brother->color = BLACK;
			RotateLeft(node->parent);
			//之后转入情况1或2
		}
		//情况1
		if (brother->color == BLACK && (brother->left->color == RED || brother->right->color == RED))
		{
			if (brother->right->color == RED) //A
			{
				brother->color = node->parent->color;
				brother->right->color == BLACK;
				node->parent->color = BLACK;
				RotateLeft(node->parent);
			}
			else   //B
			{
				RotateRight(brother);
				node->parent->right->color = node->parent->color;
				node->parent->color = BLACK;
				RotateLeft(node->parent);
			}
		}
		//情况2
		else if (brother->color == BLACK && (brother->left->color == BLACK && brother->right->color == BLACK))
		{
			while (node->parent != nullNode)  //当node不是根节点的时候
			{
				brother->color = RED;
				if (node->parent->color == RED)   //父结点原来为红色
				{
					node->parent->color = BLACK;
					break;
				}
				else  //父结点本来就是黑色
				{
					node = node->parent;
				}
			}
		}

	}
	else    //如果此节点是右结点，把左结点情况 left和right调换就可以
	{
		RB_Node* brother = node->parent->left;
		//情况3
		if (brother->color == RED)
		{
			node->parent->color = RED;
			brother->color = BLACK;
			RotateRight(node->parent);
			//之后转入情况1或2
		}
		//情况1
		if (brother->color == BLACK && (brother->right->color == RED || brother->left->color == RED))
		{
			if (brother->left->color == RED)   //A,远侄子
			{
				brother->color = node->parent->color;
				brother->left->color = BLACK;
				node->parent->color = BLACK;
				RotateRight(node->parent);
			}
			else   //B
			{
				RotateLeft(brother);
				node->parent->left->color = node->parent->color;
				node->parent->color = BLACK;
				RotateRight(node->parent);
			}
		}
		//情况2
		else if (brother->color == BLACK && (brother->right->color == BLACK && brother->left->color == BLACK))
		{
			while (node->parent != nullNode)   //当node不是根节点的时候
			{
				brother->color = RED;
				if (node->parent->color == RED)    //父结点原来为红色
				{
					node->parent->color = BLACK;
					break;
				}
				else  //父结点本来就是黑色
				{
					node = node->parent;
				}
			}
		}
	}
}

RB_Node* RB_Tree::FindMin(RB_Node* node)
{
	if (node->left == nullNode)
		return node;
	return FindMin(node->left);
}

  //中序遍历
void RB_Tree::InOrderTraverse(RB_Node* node)
{
	if (node == nullNode)
	{
		return;
	}
	else
	{
		InOrderTraverse(node->left);
		cout << node->value << endl;
		InOrderTraverse(node->right);
	}
}

void RB_Tree::clear(RB_Node* node)
{
	if (node == nullNode)
	{
		return;
	}
	else
	{
		clear(node->left);
		clear(node->right);
		delete node;
	}
};

