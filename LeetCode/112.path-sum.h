// 路径总和

// 难度：简单

// Tags
// tree

// 给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。

// 说明: 叶子节点是指没有子节点的节点。

// 示例: 
// 给定如下二叉树，以及目标和 sum = 22，

//               5
//              / \
//             4   8
//            /   / \
//           11  13  4
//          /  \      \
//         7    2      1
// 返回 true, 因为存在目标和为 22 的根节点到叶子节点的路径 5->4->11->2。

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

bool hasPathSum(TreeNode *root, int sum);

void TestPathSum()
{
    TreeNode *node4 = new TreeNode(4, new TreeNode(5), new TreeNode(1));
    TreeNode *node11 = new TreeNode(11, new TreeNode(7), new TreeNode(2));
    TreeNode *node8 = new TreeNode(8, new TreeNode(13), node4);
    TreeNode *node4_2 = new TreeNode(4, node11, nullptr);
    TreeNode *node5 = new TreeNode(5, node4_2, node8);

    bool result = hasPathSum(node5, 22);
    cout << "result is " << result << endl;
}

// // version: recurrance
// bool hasPathSum(TreeNode *root, int sum)
// {
//     if (!root)
//         return false;

//     int remain = sum - root->val;

//     if (remain == 0 && !root->left && !root->right)
//         return true;

//     return hasPathSum(root->left, remain) || hasPathSum(root->right, remain);
// }

bool hasPathSum(TreeNode *root, int sum)
{
    if (!root)
        return false;

    stack<TreeNode *> toVisit;
    stack<int> targets;

    toVisit.push(root);
    targets.push(sum - root->val);

    int target = sum;

    while (!toVisit.empty())
    {
        TreeNode *curr = toVisit.top();
        int target = targets.top();
        toVisit.pop();
        targets.pop();

        if (!curr->left && !curr->right && target == 0)
            return true;

        if (curr->left)
        {
            toVisit.push(curr->left);
            targets.push(target - curr->left->val);
        }

        if (curr->right)
        {
            toVisit.push(curr->right);
            targets.push(target - curr->right->val);
        }
    }

    return false;
}
