#include <iostream>

using namespace std;

enum NodeColor
{
	RED,
	BLACK
};

template<class KEY, class VALUE>
class RB_Node   //结点类
{
public:
	RB_Node()   //节点类构造
	{
		right = NULL;
		left = NULL;
		parent = NULL;
	}
	NodeColor RB_COLOR; //颜色
	RB_Node<KEY,VALUE>* right;  //右子树
	RB_Node<KEY,VALUE>* left;   //左子树
	RB_Node<KEY,VALUE>* parent; //父结点
	KEY key;    //键
	VALUE val;  //值
};

template<class KEY, class VALUE>
class RB_Tree
{
	//RB树类
private:
	RB_Tree(const RB_Tree& input) {}
	const RB_Tree& operator=(const RB_Tree& input) {}
	void InOrderTraverse(RB_Node<KEY,VALUE>* node); //中序遍历
	void clear(RB_Node<KEY,VALUE>* node);   //清除RB树
	//成员变量
	//RB_Node<KEY,VALUE>* m_nullNode;
	RB_Node<KEY,VALUE>* m_DBNode;
public:
	RB_Node<KEY, VALUE>* m_root;
	RB_Node<KEY, VALUE>* m_nullNode;
	RB_Tree();  //构造函数
	bool Empty();   //是否为空树
	RB_Node<KEY,VALUE>* find(KEY key);  //查找键key的值
	bool Insert(KEY KEY,VALUE val);    //插入
	void InsertFixUp(RB_Node<KEY,VALUE>* node); //插入后修复
	bool RotateLeft(RB_Node<KEY,VALUE>* node);      //左旋
	bool RotateRight(RB_Node<KEY,VALUE>* node); //右旋
	bool Delete(KEY key);   //删除
	void DoubleBlackFixUp(RB_Node<KEY,VALUE>* node);    //双黑修复
	RB_Node<KEY,VALUE>* FindMin(RB_Node<KEY,VALUE>* node);
	void InOrderTraverse()  //中序遍历外部接口
	{
		InOrderTraverse(m_root);
	}
	~RB_Tree()
	{
		clear(m_root);
		delete m_nullNode;
	}
};

template<class KEY,class VALUE>
RB_Tree<KEY,VALUE>::RB_Tree()       //构造函数
{
	this->m_nullNode = new RB_Node<KEY,VALUE>();
	this->m_root = m_nullNode;
	this->m_nullNode->right = this->m_root;
	this->m_nullNode->left = this->m_root;
	this->m_nullNode->parent = this->m_root;
	this->m_nullNode->RB_COLOR = BLACK;
	this->m_DBNode = new RB_Node<KEY,VALUE>();
	this->m_DBNode->RB_COLOR = BLACK;
	this->m_DBNode->left = m_nullNode;
	this->m_DBNode->right = m_nullNode;
};

template<class KEY, class VALUE>
bool RB_Tree<KEY,VALUE>::Empty()
{
	if (this->m_root == this->m_nullNode)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class KEY, class VALUE>
RB_Node<KEY,VALUE>* RB_Tree<KEY,VALUE>::find(KEY key)   //查找，此处可递归，参考上一篇二叉查找树
{
	RB_Node<KEY,VALUE>* index = m_root;
	while (index != m_nullNode)
	{
		if (key < index->key)
		{
			index = index->left;
		}
		else if (key > index->key)
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
template<class KEY,class VALUE>
bool RB_Tree<KEY,VALUE>::RotateLeft(RB_Node<KEY,VALUE>* node)
{
	if (node == m_nullNode || node->right == m_nullNode)
	{
		return false;   //不能旋转
	}
	RB_Node<KEY,VALUE>* lower_right = node->right;
	lower_right->parent = node->parent;
	node->right = lower_right->left;
	if (lower_right->left != m_nullNode)
	{
		lower_right->left->parent = node;
	}
	if (node->parent == m_nullNode)
	{
		m_root = lower_right;
		m_nullNode->right = m_root;
		m_nullNode->left = m_root;
		m_nullNode->parent = m_root;
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

template<class KEY,class VALUE>
bool RB_Tree<KEY,VALUE>::RotateRight(RB_Node<KEY,VALUE>* node)  //右旋，原理同左旋,left和right交换就可以
{
	if (node == m_nullNode || node->left == m_nullNode)
	{
		return false;//can't rotate    
	}
	RB_Node<KEY,VALUE>* lower_left = node->left;
	node->left = lower_left->right;
	lower_left->parent = node->parent;
	if (lower_left->right != m_nullNode)
	{
		lower_left->right->parent = node;
	}
	if (node->parent == m_nullNode) //node is root    
	{
		m_root = lower_left;
		m_nullNode->left = m_root;
		m_nullNode->right = m_root;
		m_nullNode->parent = m_root;    
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
template<class KEY,class VALUE>
bool RB_Tree<KEY,VALUE>::Insert(KEY key,VALUE val)
{
	RB_Node<KEY,VALUE>* targetNode = m_root;
	RB_Node<KEY, VALUE>* targetNodeParent = m_nullNode;

	while (targetNode != m_nullNode)
	{
		targetNodeParent = targetNode;
		if (key < targetNode->key)
		{
			targetNode = targetNode->left;
		}
		else if (key > targetNode->key)
		{
			targetNode = targetNode->right;
		}
		else
		{
			return false;
		}
	}   //此时insert_point指向要插入的点
	RB_Node<KEY,VALUE>* insert_node = new RB_Node<KEY,VALUE>(); //构造插入的结点
	insert_node->key = key;
	insert_node->val = val;
	insert_node->RB_COLOR = RED;
	insert_node->right = m_nullNode;
	insert_node->left = m_nullNode;
	if (targetNodeParent == m_nullNode)        //如果是一颗空树
	{
		m_root = insert_node;
		m_root->parent = m_nullNode;
		m_nullNode->left = m_root;
		m_nullNode->right = m_root;
		m_nullNode->parent = m_root;
	}
	else
	{
		if (key < targetNodeParent->key)
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
template<class KEY,class VALUE>
void RB_Tree<KEY,VALUE>::InsertFixUp(RB_Node<KEY,VALUE>* node)
{
	while (node->parent->RB_COLOR == RED)        //A
	{
		if (node->parent == node->parent->parent->left)    //B
		{
			RB_Node<KEY,VALUE>* uncle = node->parent->parent->right;   //C
			if (uncle->RB_COLOR == RED) //D
			{
				node->parent->RB_COLOR = BLACK;
				uncle->RB_COLOR = BLACK;
				node->parent->parent->RB_COLOR = RED;
				node = node->parent->parent;
			}
			else if (uncle->RB_COLOR == BLACK)
			{
				if (node == node->parent->right) //E
				{
					node = node->parent;
					RotateLeft(node);
				}
				//F
				node->parent->RB_COLOR = BLACK;
				node->parent->parent->RB_COLOR = RED;
				RotateRight(node->parent->parent);
			}
		}
		else    //G
		{
			RB_Node<KEY,VALUE>* uncle = node->parent->parent->left;
			if (uncle->RB_COLOR == RED)
			{
				node->parent->RB_COLOR = BLACK;
				uncle->RB_COLOR = BLACK;
				uncle->parent->RB_COLOR = RED;
				node = node->parent->parent;
			}
			else if (uncle->RB_COLOR == BLACK)
			{
				if (node == node->parent->left)
				{
					node = node->parent;
					RotateRight(node);
				}

				node->parent->RB_COLOR = BLACK;
				node->parent->parent->RB_COLOR = RED;
				RotateLeft(node->parent->parent);
			}
		}
	}
	m_root->RB_COLOR = BLACK;    //修复根节点颜色，防止被改为红色
}

/*
	删除一个结点：

*/
template<class KEY,class VALUE>
bool RB_Tree<KEY,VALUE>::Delete(KEY key)
{

	RB_Node<KEY,VALUE>* delete_point = find(key);   //找到要删除的点
	if (delete_point == m_nullNode)
	{
		return false;
	}
	if (delete_point->left != m_nullNode && delete_point->right != m_nullNode) //有两个子结点
	{
		RB_Node<KEY,VALUE>* replace_node = FindMin(delete_point->right);
		//删除点和替换点的值互换，结点颜色不换
		KEY tmpkey = delete_point->key;
		VALUE tmpval = delete_point->val;
		delete_point->key = replace_node->key;
		delete_point->val = replace_node->val;
		replace_node->key = tmpkey;
		replace_node->val = tmpval;
		delete_point = replace_node;
	}
	RB_Node<KEY,VALUE>* delete_point_child;
	if (delete_point->RB_COLOR == RED)  //若该节点为红色
	{
		if (delete_point == delete_point->parent->left)   //如果是左孩子
		{
			delete_point->parent->left = m_nullNode;
		}
		else   //如果是右孩子
		{
			delete_point->parent->right = m_nullNode;
		}
		delete delete_point;
	}

	else if (delete_point->right != m_nullNode) //如果右结点不为空,此时要删除的结点肯定为黑色，且右结点肯定为红色
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
		delete_point->right->RB_COLOR = BLACK;    //右结点颜色改为黑色
		delete delete_point;
	}
	else if (delete_point->left != m_nullNode)  //如果左结点不为空（未经过替换），与右节点不为空操作一样
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
		delete_point->left->RB_COLOR = BLACK; //右结点颜色改为黑色
		delete delete_point;
	}
	else    //无子节点的情况
	{
		//此时唯一剩下情况为，要删除结点为黑色且无子结点
		if (delete_point->parent == m_nullNode)  //如果要删除的是根节点
		{
			m_root = m_nullNode;
			m_nullNode->parent = m_root;
			m_nullNode->left = m_root;
			m_nullNode->left = m_root;
			delete delete_point;
		}
		else
		{


			RB_Node<KEY,VALUE>* tmp = delete_point->parent;
			if (delete_point == delete_point->parent->left)   //如果要删除结点为左节点
			{

				delete delete_point;
				tmp->left = m_DBNode;
				m_DBNode->parent = tmp;
				DoubleBlackFixUp(m_DBNode);
				tmp->left = m_nullNode;
			}
			else    //如果要删除结点为右节点
			{

				delete delete_point;
				tmp->right = m_DBNode;
				m_DBNode->parent = tmp;
				DoubleBlackFixUp(m_DBNode);
				tmp->right = m_nullNode;
			}
		}
	}
}

/*
	双黑修复
*/
template<class KEY,class VALUE>
void RB_Tree<KEY,VALUE>::DoubleBlackFixUp(RB_Node<KEY,VALUE>* node) //传过来的参数都是双黑结点
{

	if (node == node->parent->left)  //如果此结点是左结点
	{

		RB_Node<KEY,VALUE>* brother = node->parent->right;
		//情况3
		if (brother->RB_COLOR == RED)
		{
			node->parent->RB_COLOR = RED;
			brother->RB_COLOR = BLACK;
			RotateLeft(node->parent);
			//之后转入情况1或2
		}
		//情况1
		if (brother->RB_COLOR == BLACK && (brother->left->RB_COLOR == RED || brother->right->RB_COLOR == RED))
		{
			if (brother->right->RB_COLOR == RED) //A
			{
				brother->RB_COLOR = node->parent->RB_COLOR;
				brother->right->RB_COLOR == BLACK;
				node->parent->RB_COLOR = BLACK;
				RotateLeft(node->parent);
			}
			else   //B
			{
				RotateRight(brother);
				node->parent->right->RB_COLOR = node->parent->RB_COLOR;
				node->parent->RB_COLOR = BLACK;
				RotateLeft(node->parent);
			}
		}
		//情况2
		else if (brother->RB_COLOR == BLACK && (brother->left->RB_COLOR == BLACK && brother->right->RB_COLOR == BLACK))
		{
			while (node->parent != m_nullNode)  //当node不是根节点的时候
			{
				brother->RB_COLOR = RED;
				if (node->parent->RB_COLOR == RED)   //父结点原来为红色
				{
					node->parent->RB_COLOR = BLACK;
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
		RB_Node<KEY,VALUE>* brother = node->parent->left;
		//情况3
		if (brother->RB_COLOR == RED)
		{
			node->parent->RB_COLOR = RED;
			brother->RB_COLOR = BLACK;
			RotateRight(node->parent);
			//之后转入情况1或2
		}
		//情况1
		if (brother->RB_COLOR == BLACK && (brother->right->RB_COLOR == RED || brother->left->RB_COLOR == RED))
		{
			if (brother->left->RB_COLOR == RED)   //A,远侄子
			{
				brother->RB_COLOR = node->parent->RB_COLOR;
				brother->left->RB_COLOR = BLACK;
				node->parent->RB_COLOR = BLACK;
				RotateRight(node->parent);
			}
			else   //B
			{
				RotateLeft(brother);
				node->parent->left->RB_COLOR = node->parent->RB_COLOR;
				node->parent->RB_COLOR = BLACK;
				RotateRight(node->parent);
			}
		}
		//情况2
		else if (brother->RB_COLOR == BLACK && (brother->right->RB_COLOR == BLACK && brother->left->RB_COLOR == BLACK))
		{
			while (node->parent != m_nullNode)   //当node不是根节点的时候
			{
				brother->RB_COLOR = RED;
				if (node->parent->RB_COLOR == RED)    //父结点原来为红色
				{
					node->parent->RB_COLOR = BLACK;
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

template<class KEY,class VALUE>
RB_Node<KEY,VALUE>* RB_Tree<KEY,VALUE>::FindMin(RB_Node<KEY,VALUE>* node)
{
	if (node->left == m_nullNode)
		return node;
	return FindMin(node->left);
}

template<class KEY,class VALUE>    //中序遍历
void RB_Tree<KEY,VALUE>::InOrderTraverse(RB_Node<KEY,VALUE>* node)
{
	if (node == m_nullNode)
	{
		return;
	}
	else
	{
		InOrderTraverse(node->left);
		cout << node->key << endl;
		InOrderTraverse(node->right);
	}
}

template<class KEY,class VALUE>
void RB_Tree<KEY,VALUE>::clear(RB_Node<KEY,VALUE>* node)
{
	if (node == m_nullNode)
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

