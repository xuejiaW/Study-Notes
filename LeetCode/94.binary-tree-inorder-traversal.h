// 二叉树的中序遍历

// 难度：中等

// 标签：
// 栈 | 树

// 给定一个二叉树，返回它的中序遍历。

// 示例:

// 输入: [1,null,2,3]
//    1
//     \
//      2
//     /
//    3

// 输出: [1,3,2]

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

vector<int> inorderTraversal(TreeNode *root);

void TestInorderTraversal()
{
    TreeNode *tree3 = new TreeNode(3);
    TreeNode *tree2 = new TreeNode(2, tree3, nullptr);
    TreeNode *tree1 = new TreeNode(1, nullptr, tree2);
    vector<int> result = inorderTraversal(tree1);
    for (int i : result)
        cout << i << endl;
}

// // Version: Recursive method
// vector<int> inorderTraversal(TreeNode *root)
// {
//     if (root == nullptr)
//         return vector<int>();

//     vector<int> left = inorderTraversal(root->left);

//     left.push_back(root->val);

//     vector<int> right = inorderTraversal(root->right);
//     left.insert(left.end(), right.begin(), right.end());
//     return left;
// }

// // Version: Iterative method with stack
// vector<int> inorderTraversal(TreeNode *root)
// {
//     vector<int> result;

//     if (!root)
//         return result;

//     stack<TreeNode *> toVisitNodes;
//     TreeNode *current = root;
//     while (true)
//     {
//         while (current)
//         {
//             toVisitNodes.push(current);
//             current = current->left;
//         }

//         if (toVisitNodes.empty())
//             break;

//         current = toVisitNodes.top();
//         toVisitNodes.pop();
//         result.push_back(current->val);

//         current = current->right;
//     }

//     return result;
// }

// Version: Morris Traversal
vector<int> inorderTraversal(TreeNode *root)
{
    vector<int> result;
    while (root)
    {
        if (root->left)
        {
            TreeNode *rightestNodeInLeft = root->left;
            while (rightestNodeInLeft->right && rightestNodeInLeft->right != root)
            {
                rightestNodeInLeft = rightestNodeInLeft->right;
            }
            if (!rightestNodeInLeft->right)
            {
                rightestNodeInLeft->right = root;
                root = root->left;
            }
            else
            {
                rightestNodeInLeft->right = nullptr;
                result.push_back(root->val);
                root = root->right;
            }
        }
        else
        {
            result.push_back(root->val);
            root = root->right;
        }
    }
    return result;
}