// 二叉树的直径

// 难度：中等

// Tags
// tree

// 给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。这条路径可能穿过也可能不穿过根结点。

// 给定二叉树

//           1
//          / \
//         2   3
//        / \     
//       4   5    
// 返回 3, 它的长度是路径 [4,2,1,3] 或者 [5,2,1,3]。

#include "parser.h"
#include "debug.h"
#include <queue>
#include <algorithm>

int diameterOfBinaryTree(TreeNode *root);
void TestDiameterOfBinaryTree()
{
    TreeNode *root = parse2Tree("[1,2,3,4,5]");
    int result = diameterOfBinaryTree(root);
    cout << result << endl;
}

// // Version: recurrance，duplicate calculation
// int maxDepthTree(TreeNode *root);
// int diameterOfBinaryTree(TreeNode *root)
// {
//     if (!root)
//         return 0;
//     int left = diameterOfBinaryTree(root->left);
//     int right = diameterOfBinaryTree(root->right);
//     //cross should not puls 1, because result is calculating edge
//     int cross = maxDepthTree(root->left) + maxDepthTree(root->right);

//     return max(left, max(right, cross));
// }

// int maxDepthTree(TreeNode *root)
// {
//     if (!root)
//         return 0;
//     return max(maxDepthTree(root->left), maxDepthTree(root->right)) + 1;
// }

// Version: recurrance optimization, calculating result while reduce duplicate operation
int maxDepthTree(TreeNode *root, int &maxDiameter);
int diameterOfBinaryTree(TreeNode *root)
{
    if (!root)
        return 0;

    int maxDiameter = 1; // 1 for root
    maxDepthTree(root, maxDiameter);

    return maxDiameter - 1; // node to edge
}

int maxDepthTree(TreeNode *root, int &maxDiameter)
{
    if (!root)
        return 0;

    int left = maxDepthTree(root->left, maxDiameter);
    int right = maxDepthTree(root->right, maxDiameter);

    maxDiameter = max(maxDiameter, left + right + 1);

    return max(right, left) + 1;
}
