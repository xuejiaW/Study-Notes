// 二叉树的前序遍历

// 难度：中等

// Tags:

// stack | tree

// 给定一个二叉树，返回它的 前序 遍历。

//  示例:

// 输入: [1,null,2,3]  
//    1
//     \
//      2
//     /
//    3 

// 输出: [1,2,3]

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

vector<int> preorderTraversal(TreeNode *root);

void TestPreorderTraversal()
{
    TreeNode *tree3 = new TreeNode(3);
    TreeNode *tree2 = new TreeNode(2, tree3, nullptr);
    TreeNode *tree1 = new TreeNode(1, nullptr, tree2);
    vector<int> result = preorderTraversal(tree1);
    for (int i : result)
        cout << i << endl;
}

// // Version: interactive
// vector<int> preorderTraversal(TreeNode *root)
// {
//     if (root == nullptr)
//         return vector<int>();

//     vector<int> result;
//     stack<TreeNode *> toVisitNodes;
//     toVisitNodes.push(root);

//     TreeNode *curr = nullptr;
//     while (!toVisitNodes.empty())
//     {
//         curr = toVisitNodes.top();
//         toVisitNodes.pop();

//         result.push_back(curr->val);
//         if (curr->right)
//             toVisitNodes.push(curr->right);
//         if (curr->left)
//             toVisitNodes.push(curr->left);
//     }

//     return result;
// }

// // Version: recurrance
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