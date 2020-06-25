// 二叉树的最近公共祖先

// 难度：中等

// Tags:
// tree

// 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

// 例如，root = [3,5,1,6,2,0,8,null,null,7,4]

// 示例 1:
// 输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
// 输出: 3
// 解释: 节点 5 和节点 1 的最近公共祖先是节点 3。

// 示例 2:
// 输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
// 输出: 5
// 解释: 节点 5 和节点 4 的最近公共祖先是节点 5。因为根据定义最近公共祖先节点可以为节点本身。

#include <iostream>
#include <queue>
#include <unordered_map>
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
    TreeNode *node1 = new TreeNode(1, new TreeNode(0), new TreeNode(8));
    TreeNode *node2 = new TreeNode(2, new TreeNode(7), new TreeNode(4));
    TreeNode *node5 = new TreeNode(5, new TreeNode(6), node2);
    TreeNode *node3 = new TreeNode(3, node5, node1);
    TreeNode *result = lowestCommonAncestor(node3, node5, node1);
    cout << " result is " << result->val << endl;
}

// // Version: recurrance
// TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
// {
//     if (root == nullptr || p == root || q == root)
//         return root;

//     TreeNode *left = lowestCommonAncestor(root->left, p, q);
//     TreeNode *right = lowestCommonAncestor(root->right, p, q);
//     if (left == nullptr)
//         return right;
//     if (right == nullptr)
//         return left;
//     return root;
// }

// Version: iterative with unordered_map
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    unordered_map<TreeNode *, TreeNode *> child2ParentMap;
    unordered_map<TreeNode *, bool> visitedMap;

    child2ParentMap[root] = nullptr;

    // level traversal
    queue<TreeNode *> toVisited;
    toVisited.push(root);
    while (!toVisited.empty())
    {
        TreeNode *curr = toVisited.front();
        toVisited.pop();
        if (curr->left)
        {
            child2ParentMap[curr->left] = curr;
            toVisited.push(curr->left);
        }
        if (curr->right)
        {
            child2ParentMap[curr->right] = curr;
            toVisited.push(curr->right);
        }
    }

    // from p to root
    while (p)
    {
        visitedMap[p] = true;
        p = child2ParentMap[p];
    }

    // from q to root
    while (q)
    {
        // means that this root has been visited by p
        if (visitedMap[q])
            return q;
        q = child2ParentMap[q];
    }

    return root;
}
