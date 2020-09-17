
//  @lc app=leetcode.cn id=124 lang=cpp

//  [124] 二叉树中的最大路径和

//  https://leetcode-cn.com/problems/binary-tree-maximum-path-sum/description/

//  algorithms
//  Hard

//  给定一个非空二叉树，返回其最大路径和。

//  本题中，路径被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。该路径至少包含一个节点，且不一定经过根节点。

//  示例 1：

//  输入：[1,2,3]

//  ⁠      1
//  ⁠     / \
//  ⁠    2   3

//  输出：6

//  示例 2：

//  输入：[-10,9,20,null,null,15,7]

//  -10
//  / \
//  9  20
//  /  \
//  15   7

//  输出：42

#include "parser.h"
#include "debug.h"
#include "climits"

int maxPathSum(TreeNode *root);

void TestMaxPathSum()
{
    // TreeNode *root = parse2Tree("[-10,9,20,null,null,15,7]");
    // TreeNode *root = parse2Tree("[2,-1]");
    TreeNode *root = parse2Tree("[-3]");
    cout << maxPathSum(root) << endl;
}

int GetPartMax(TreeNode *root, int &result);
int maxPathSum(TreeNode *root)
{
    if (!root)
        return 0;
    int result = root->val;
    GetPartMax(root, result);
    return result;
}

int GetPartMax(TreeNode *root, int &result)
{
    if (!root)
        return 0;

    int leftPart = max(GetPartMax(root->left, result), 0);
    int rightPart = max(GetPartMax(root->right, result), 0);

    int contribution = root->val + max(leftPart, rightPart);

    result = max(result, root->val + leftPart + rightPart);

    return contribution;
}
