// 将二叉搜索树转化为排序的双向链表

// 难度：中等

// Tags：
// tree

// 将一个 二叉搜索树 就地转化为一个 已排序的双向循环链表 。

// 对于双向循环列表，你可以将左右孩子指针作为双向循环链表的前驱和后继指针，第一个节点的前驱是最后一个节点，最后一个节点的后继是第一个节点。

// 特别地，我们希望可以 就地 完成转换操作。当转化完成以后，树中节点的左指针需要指向前驱，树中节点的右指针需要指向后继。还需要返回链表中最小元素的指针。

// 输入：root = [2,1,3]
// 输出：[1,2,3]

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Node
{
public:
    int val;
    Node *left;
    Node *right;

    Node() {}

    Node(int _val)
    {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node *_left, Node *_right)
    {
        val = _val;
        left = _left;
        right = _right;
    }
};

Node *treeToDoublyList(Node *root)
{
    if (!root)
        return root;

    // push the inorder result to this vector
    // the element in this vector is ascending order
    vector<Node *> nodesVec;
    stack<Node *> toVisit;

    // Inorder traversal
    Node *curr = root;
    while (true)
    {
        while (curr)
        {
            toVisit.push(curr);
            curr = curr->left;
        }

        if (toVisit.empty())
            break;

        curr = toVisit.top();
        toVisit.pop();

        nodesVec.push_back(curr);

        curr = curr->right;
    }

    // set pre/next pointer
    nodesVec.front()->left = nodesVec.back();
    for (int i = 0; i != nodesVec.size(); ++i)
    {
        if (i != 0)
            nodesVec[i]->left = nodesVec[i - 1];
        if (i != nodesVec.size() - 1)
            nodesVec[i]->right = nodesVec[i + 1];
    }
    nodesVec.back()->right = nodesVec.front();

    return nodesVec.front();
}