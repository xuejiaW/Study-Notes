
//  @lc app=leetcode.cn id=116 lang=cpp

//  [116] 填充每个节点的下一个右侧节点指针

//  https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node/description/

// Tags
// tree | depth-first-search

// Medium

//  给定一个完美二叉树，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：

//  struct Node {
//  ⁠ int val;
//  ⁠ Node *left;
//  ⁠ Node *right;
//  ⁠ Node *next;
//  }

//  填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。

//  初始状态下，所有 next 指针都被设置为 NULL。

//  示例：

//  输入：{"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":null,"right":null,"val":4},"next":null,"right":{"$id":"4","left":null,"next":null,"right":null,"val":5},"val":2},"next":null,"right":{"$id":"5","left":{"$id":"6","left":null,"next":null,"right":null,"val":6},"next":null,"right":{"$id":"7","left":null,"next":null,"right":null,"val":7},"val":3},"val":1}

//  输出：{"$id":"1","left":{"$id":"2","left":{"$id":"3","left":null,"next":{"$id":"4","left":null,"next":{"$id":"5","left":null,"next":{"$id":"6","left":null,"next":null,"right":null,"val":7},"right":null,"val":6},"right":null,"val":5},"right":null,"val":4},"next":{"$id":"7","left":{"$ref":"5"},"next":null,"right":{"$ref":"6"},"val":3},"right":{"$ref":"4"},"val":2},"next":null,"right":{"$ref":"7"},"val":1}

//  解释：给定二叉树如图 A 所示，你的函数应该填充它的每个 next 指针，以指向其下一个右侧节点，如图 B 所示。

//  提示：

//  你只能使用常量级额外空间。
//  使用递归解题也符合要求，本题中递归程序占用的栈空间不算做额外的空间复杂度。

#include "parser.h"
#include "debug.h"

class Node
{
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

// Version: level order travel
// Node *connect(Node *root)
// {
//     if (root == nullptr)
//         return nullptr;

//     queue<Node *> toVisit;
//     toVisit.push(root);
//     while (!toVisit.empty())
//     {
//         int nodesNum = toVisit.size();
//         Node *previous = nullptr;
//         Node *curr = nullptr;

//         for (int i = 0; i != nodesNum; ++i)
//         {
//             curr = toVisit.front();
//             toVisit.pop();
//             if (previous != nullptr)
//                 previous->next = curr;

//             if (curr->left)
//                 toVisit.push(curr->left);
//             if (curr->right)
//                 toVisit.push(curr->right);

//             previous = curr;
//         }
//     }

//     return root;
// }

Node *connect(Node *root)
{
    if (root = nullptr)
        return nullptr;

    Node *curr = root;
    Node *leftMost = root;

    while (curr && curr->left)
    {
        curr->left->next = curr->right;
        if (curr->next != nullptr)
        {
            curr->right->next = curr->next->left;
            curr = curr->next;
        }
        else
        {
            curr = leftMost->left;
            leftMost = curr;
        }
    }

    return root;
}

// @lc code=end
