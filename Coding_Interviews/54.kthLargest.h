// 二叉搜索树的第k大节点

// 给定一棵二叉搜索树，请找出其中第k大的节点。

// 难度：简单

// Tags: tree

// 示例 1:

// 输入: root = [3,1,4,null,2], k = 1
//    3
//   / \
//  1   4
//   \
//    2
// 输出: 4
// 示例 2:

// 输入: root = [5,3,6,2,4,null,null,1], k = 3
//        5
//       / \
//      3   6
//     / \
//    2   4
//   /
//  1
// 输出: 4

#include <iostream>
#include <stack>

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

int kthLargest(TreeNode *root, int k);

void TestKthLargest()
{
    TreeNode *node1 = new TreeNode(1, nullptr, new TreeNode(2));
    TreeNode *node4 = new TreeNode(4);
    TreeNode *node3 = new TreeNode(3, node1, node4);

    int result = kthLargest(node3, 2);

    cout << "result " << result << endl;
}

// Version: use reversed inorder traversal
int kthLargest(TreeNode *root, int k)
{
    int result = 0;
    stack<TreeNode *> toVisit;

    TreeNode *curr = root;

    while (k)
    {
        while (curr)
        {
            toVisit.push(curr);
            curr = curr->right;
        }
        if (toVisit.empty())
            break;

        curr = toVisit.top();
        toVisit.pop();

        if ((--k) == 0)
            result = curr->val;

        curr = curr->left;
    }

    return result;
}