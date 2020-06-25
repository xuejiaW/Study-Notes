// 对称二叉树

// 难度：简单

// Tags
// tree | depth-first-search | breadth-first-search

// 给定一个二叉树，检查它是否是镜像对称的。

 

// 例如，二叉树 [1,2,2,3,4,4,3] 是对称的。

//     1
//    / \
//   2   2
//  / \ / \
// 3  4 4  3
 

// 但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:

//     1
//    / \
//   2   2
//    \   \
//    3    3

#include <queue>
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

bool isSymmetric(TreeNode *root);

void TestSymmetricTree()
{
    // TreeNode *node234 = new TreeNode(2, new TreeNode(3), new TreeNode(4));
    // TreeNode *node243 = new TreeNode(2, new TreeNode(4), new TreeNode(3));
    // TreeNode *node1 = new TreeNode(1, node234, node243);

    TreeNode *node234 = new TreeNode(2, nullptr, new TreeNode(3));
    TreeNode *node243 = new TreeNode(2,  nullptr,new TreeNode(3));
    TreeNode *node1 = new TreeNode(1, node234, node243);

    bool result = isSymmetric(node1);
    cout << "result is " << result;
}

// Can not use inorder result to judge, because some asymmetry tree with empty leaf may have the same inorder result

// // Version: recurrance, like DFS
// bool isSymmetric(TreeNode *left, TreeNode *right);
// bool isSymmetric(TreeNode *root)
// {
//     if (root == nullptr)
//         return true;

//     return isSymmetric(root, root);
// }

// bool isSymmetric(TreeNode *left, TreeNode *right)
// {
//     if (!left && !right) // both empty
//         return true;

//     if (!left || !right) // only one empty
//         return false;

//     return (left->val == right->val) && isSymmetric(left->left, right->right) && isSymmetric(left->right, right->left);
// }

// // Version: iteractive, like BFS
bool isSymmetric(TreeNode *root)
{
    if (!root || (!root->left && !root->right))
        return true;
    if (!root->left || !root->right)
        return false;

    queue<TreeNode *> toCheck;
    toCheck.push(root->left);
    toCheck.push(root->right);

    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    while (!toCheck.empty())
    {
        left = toCheck.front();
        toCheck.pop();

        right = toCheck.front();
        toCheck.pop();

        if (!left && !right) //both empty
            continue;

        if ((!left || !right) || (left->val != right->val)) // only one empty or the value not equal
            return false; 

        toCheck.push(left->left);
        toCheck.push(right->right);

        toCheck.push(left->right);
        toCheck.push(right->left);
    }

    return true;
}
