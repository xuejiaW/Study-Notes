// 二叉树的右视图

// 难度：中等

// Tags:
// Tree | Breadth first searching

// 给定一棵二叉树，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

// 示例:

// 输入: [1,2,3,null,5,null,4]
// 输出: [1, 3, 4]
// 解释:

//    1            <---
//  /   \
// 2     3         <---
//  \     \
//   5     4       <---


#include <vector>
#include <iostream>
#include <queue>

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

vector<int> rightSideView(TreeNode *root);

void TestRightSideView()
{
    TreeNode *treeNode_2 = new TreeNode(2, nullptr, new TreeNode(5));
    TreeNode *treeNode_3 = new TreeNode(3, nullptr, new TreeNode(4));
    TreeNode *treeNode_1 = new TreeNode(1, treeNode_2, treeNode_3);
    vector<int> result = rightSideView(treeNode_1);
    for (auto i : result)
        cout << i << endl;
}

// Version: like level traversal
vector<int> rightSideView(TreeNode *root)
{
    vector<int> result;
    if (!root)
        return result;

    queue<TreeNode *> toVisit;
    toVisit.push(root);

    while (!toVisit.empty())
    {
        int size = toVisit.size();
        for (int i = 0; i != size; ++i)
        {
            TreeNode *node = toVisit.front();
            toVisit.pop();
            if (i == size - 1)
                result.push_back(node->val);

            if (node->left)
                toVisit.push(node->left);
            if (node->right)
                toVisit.push(node->right);
        }
    }
    return result;
}
