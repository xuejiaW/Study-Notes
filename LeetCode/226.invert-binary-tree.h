// 翻转二叉树

// 难度：简单

// Tags:

// tree

// 翻转一棵二叉树。

// 示例：

// 输入：

//      4
//    /   \
//   2     7
//  / \   / \
// 1   3 6   9
// 输出：

//      4
//    /   \
//   7     2
//  / \   / \
// 9   6 3   1


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

vector<int> preorderTraversal(TreeNode *root)
{
    if (root == nullptr)
        return vector<int>();

    vector<int> result{root->val};

    vector<int> left = preorderTraversal(root->left);
    result.insert(result.end(), left.begin(), left.end());

    vector<int> right = preorderTraversal(root->right);
    result.insert(result.end(), right.begin(), right.end());

    return result;
}

TreeNode *invertTree(TreeNode *root);

void TestInvertTree()
{
    TreeNode *node7 = new TreeNode(7, new TreeNode(6), new TreeNode(9));
    TreeNode *node2 = new TreeNode(2, new TreeNode(1), new TreeNode(3));
    TreeNode *node4 = new TreeNode(4, node2, node7);

    vector<int> result = preorderTraversal(node4);
    for (int i : result)
        cout << i << endl;

    result = preorderTraversal(invertTree(node4));
    for (int i : result)
        cout << i << endl;
}

// // Version: iterative
// TreeNode *invertTree(TreeNode *root)
// {
//     if (!root)
//         return nullptr;

//     stack<TreeNode *> toVisit;
//     toVisit.push(root);

//     TreeNode *curr = nullptr;
//     while (!toVisit.empty())
//     {
//         curr = toVisit.top();
//         toVisit.pop();

//         swap(curr->left, curr->right);

//         if (curr->right)
//             toVisit.push(curr->right);
//         if (curr->left)
//             toVisit.push(curr->left);
//     }

//     return root;
// }

// Version: recurrance
TreeNode *invertTree(TreeNode *root)
{
    if (!root)
        return nullptr;

    swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}