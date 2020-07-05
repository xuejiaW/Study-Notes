// 二叉树展开为链表

// 难度：中等

// Tags
// tree | depth-first-search

// 给定一个二叉树，原地将它展开为一个单链表。

//   1
//    / \
//   2   5
//  / \   \
// 3   4   6
// 将其展开为：

// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
//          \
//           6

#include "parser.h"
#include "debug.h"
#include <stack>

void flatten(TreeNode *root);

void TestFlatten()
{
    TreeNode *node = parse2Tree("[1,2,5,3,4,7,6,null,11,8,null,null,9,null,null]");
    flatten(node);
    DebugTree(node);
}

void flatten(TreeNode *root)
{
    if (!root)
        return;
    while ((root))
    {
        if (!root->left)
            root = root->right;
        else
        {
            TreeNode *rightestInLeft = root->left;
            while (rightestInLeft->right)
                rightestInLeft = rightestInLeft->right;
            rightestInLeft->right = root->right;
            root->right = root->left;
            root->left = nullptr;
        }
    }
}

// // Version: preorder with stack
void flatten(TreeNode *root)
{
    if (!root)
        return;

    TreeNode *curr = root;

    stack<TreeNode *> toInsert;

    while (curr)
    {
        if (curr->left)
        {
            if (curr->right)
                toInsert.push(curr->right);
            curr->right = curr->left;
            curr->left = nullptr;
        }
        else if (!curr->right && !toInsert.empty())
        {
            TreeNode *node = toInsert.top();
            toInsert.pop();
            curr->right = node;
        }
        curr = curr->right;
    }
}
