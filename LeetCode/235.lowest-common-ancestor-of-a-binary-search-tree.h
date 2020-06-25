// 二叉搜索树的最近公共祖先

// 难度：简单

// 给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。

// 例如， root = [6,2,8,0,4,7,9,null,null,3,5]

// 示例 1:

// 输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
// 输出: 6
// 解释: 节点 2 和节点 8 的最近公共祖先是 6。
// 示例 2:

// 输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
// 输出: 2
// 解释: 节点 2 和节点 4 的最近公共祖先是 2, 因为根据定义最近公共祖先节点可以为节点本身。

#include <iostream>
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

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q);

void TestLowestCommonAncester()
{
    TreeNode *node8 = new TreeNode(8, new TreeNode(7), new TreeNode(9));
    TreeNode *node4 = new TreeNode(3, new TreeNode(3), new TreeNode(5));
    TreeNode *node2 = new TreeNode(2, new TreeNode(0), node4);
    TreeNode *node6 = new TreeNode(6, node2, node4);
    TreeNode *result = lowestCommonAncestor(node6, node2, node8);
    cout << " result is " << result->val << endl;
}

// // Version: recurrance
// TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
// {
//     int rootVal = root->val;
//     int qVal = q->val;
//     int pVal = p->val;

//     if ((pVal <= rootVal && qVal >= rootVal) || (pVal >= rootVal && qVal <= rootVal))
//         return root;

//     if (pVal < rootVal && qVal < rootVal)
//         return lowestCommonAncestor(root->left, p, q);
//     else
//         return lowestCommonAncestor(root->right, p, q);
// }

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    int rootVal = root->val;
    int qVal = q->val;
    int pVal = p->val;
    while (true)
    {
        if (pVal < rootVal && qVal < rootVal)
        {
            root = root->left;
            rootVal = root->val;
        }
        else if (pVal > rootVal && qVal > rootVal)
        {
            root = root->right;
            rootVal = root->val;
        }
        else
            break;
    }
    return root;
}
