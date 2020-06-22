// 二叉树的后序遍历

// 难度：困难

// Tags:

// stack | tree

// 给定一个二叉树，返回它的 后序 遍历。

// 示例:

// 输入: [1,null,2,3]  
//    1
//     \
//      2
//     /
//    3 

// 输出: [3,2,1]

#include <iostream>
#include <vector>
#include <unordered_set>
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

vector<int> postorderTraversal(TreeNode *root);

void TestPostorderTraversal()
{
    TreeNode *tree3 = new TreeNode(3);
    TreeNode *tree2 = new TreeNode(2, tree3, nullptr);
    TreeNode *tree1 = new TreeNode(1, nullptr, tree2);
    vector<int> result = postorderTraversal(tree1);
    for (int i : result)
        cout << i << endl;
}

// Version: use reverse order output

vector<int> postorderTraversal(TreeNode *root)
{
    vector<int> resultReverse;

    if (!root)
        return resultReverse;

    stack<TreeNode *> toVisit;
    toVisit.push(root);

    while (!toVisit.empty())
    {
        TreeNode *curr = toVisit.top();
        toVisit.pop();

        resultReverse.push_back(curr->val);

        if (curr->left)
            toVisit.push(curr->left);
        if (curr->right)
            toVisit.push(curr->right);
    }

    vector<int> result(resultReverse.rbegin(), resultReverse.rend());

    return result;
}

// // Version: recurrance
// vector<int> postorderTraversal(TreeNode *root)
// {
//     if (!root)
//         return vector<int>();

//     vector<int> result;
//     vector<int> left = postorderTraversal(root->left);
//     vector<int> right = postorderTraversal(root->right);

//     result.insert(result.end(), left.begin(), left.end());
//     result.insert(result.end(), right.begin(), right.end());
//     result.push_back(root->val);

//     return result;
// }

// // Version: iterative
// vector<int> postorderTraversal(TreeNode *root)
// {
//     vector<int> result;

//     if (!root)
//         return result;

//     stack<TreeNode *> toVisit;
//     unordered_set<TreeNode *> visited;

//     toVisit.push(root);
//     visited.insert(root);

//     while (!toVisit.empty())
//     {
//         TreeNode *curr = toVisit.top();
//         bool leftVisited = true, rightVisited = true;

//         if (curr->right && visited.find(curr->right) == visited.end())
//         {
//             rightVisited = false;
//             visited.insert(curr->right);
//             toVisit.push(curr->right);
//         }

//         if (curr->left && visited.find(curr->left) == visited.end())
//         {
//             leftVisited = false;
//             visited.insert(curr->left);
//             toVisit.push(curr->left);
//         }

//         if (leftVisited && rightVisited)
//         {
//             result.push_back(curr->val);
//             toVisit.pop();
//         }
//     }

//     return result;
// }
