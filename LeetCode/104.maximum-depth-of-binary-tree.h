// 二叉树的最大深度

// 难度：简单

// Tags
// tree | breadth-first-search | depth-first-search

// 给定一个二叉树，找出其最大深度。

// 二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

// 说明: 叶子节点是指没有子节点的节点。

// 示例：
// 给定二叉树 [3,9,20,null,null,15,7]，

//     3
//    / \
//   9  20
//     /  \
//    15   7
// 返回它的最大深度 3 。

#include <iostream>
#include <vector>
#include <queue>
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

int maxDepth(TreeNode *root);
void TestMaxDepth()
{
    TreeNode *tree3 = new TreeNode(3);
    TreeNode *tree2 = new TreeNode(2, tree3, nullptr);
    TreeNode *tree1 = new TreeNode(1, nullptr, tree2);

    int result = maxDepth(tree1);
    cout << "result is " << result << endl;
}

// // Version: use recurrance, DFS
// int maxDepth(TreeNode *root)
// {
//     if (!root)
//         return 0;

//     return max(maxDepth(root->right), maxDepth(root->left)) + 1;
// }

// Version: iterative, using level-order, BFS
int maxDepth(TreeNode *root)
{
    if (!root)
        return 0;

    queue<TreeNode *> toVisit;
    toVisit.push(root);

    int result = 0;

    while (!toVisit.empty())
    {
        int levelNum = toVisit.size();
        for (int i = 0; i != levelNum; ++i)
        {
            TreeNode *node = toVisit.front();
            toVisit.pop();
            if (node->left)
                toVisit.push(node->left);
            if (node->right)
                toVisit.push(node->right);
        }
        ++result;
    }

    return result;
}
