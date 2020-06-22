// 路径总和 II

// 难度：中等

// Tags:

// tree | back tracking

// 给定一个二叉树和一个目标和，找到所有从根节点到叶子节点路径总和等于给定目标和的路径。

// 说明: 叶子节点是指没有子节点的节点。

// 示例:
// 给定如下二叉树，以及目标和 sum = 22，

//               5
//              / \
//             4   8
//            /   / \
//           11  13  4
//          /  \    / \
//         7    2  5   1
// 返回:

// [
//    [5,4,11,2],
//    [5,8,4,5]
// ]

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

vector<vector<int>> pathSum(TreeNode *root, int sum);

void TestPathSum()
{
    TreeNode *node4 = new TreeNode(4, new TreeNode(5), new TreeNode(1));
    TreeNode *node11 = new TreeNode(11, new TreeNode(7), new TreeNode(2));
    TreeNode *node8 = new TreeNode(8, new TreeNode(13), node4);
    TreeNode *node4_2 = new TreeNode(4, node11, nullptr);
    TreeNode *node5 = new TreeNode(5, node4_2, node8);

    vector<vector<int>> result = pathSum(node5, 22);
    for (auto vec : result)
    {
        for (auto i : vec)
        {
            cout << i << " ";
        }
        cout << endl;
    }
}

// Version : backTracking
void pathSum(vector<vector<int>> &result, vector<int> &solution, TreeNode *root, int sum);

vector<vector<int>> pathSum(TreeNode *root, int sum)
{
    vector<vector<int>> result;

    if (!root)
        return result;

    vector<int> solution;

    pathSum(result, solution, root, sum);

    return result;
}

void pathSum(vector<vector<int>> &result, vector<int> &solution, TreeNode *root, int sum)
{
    // required sum may < 0, so here not to check sum
    if (root == nullptr)
        return;

    solution.push_back(root->val);

    // solution required to be the path to LEAF, so check whether there are left and right
    int remain = sum - root->val;
    if (remain == 0 && !root->left && !root->right)
    {
        result.push_back(solution);
        return;
    }

    if (root->left)
    {
        pathSum(result, solution, root->left, remain);
        solution.pop_back();
    }

    if (root->right)
    {
        pathSum(result, solution, root->right, remain);
        solution.pop_back();
    }
}

// Version: Dynamic Programming
