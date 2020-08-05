// 二叉搜索树中第K小的元素

// 难度：中等

// Tags
// binary-search | tree

// 给定一个二叉搜索树，编写一个函数 kthSmallest 来查找其中第 k 个最小的元素。

// 说明：

// 你可以假设 k 总是有效的，1 ≤ k ≤ 二叉搜索树元素个数。

// 示例 1:

// 输入: root = [3,1,4,null,2], k = 1
//    3
//   / \
//  1   4
//   \
//    2
// 输出: 1
// 示例 2:

// 输入: root = [5,3,6,2,4,null,null,1], k = 3
//        5
//       / \
//      3   6
//     / \
//    2   4
//   /
//  1
// 输出: 3


#include "parser.h"
#include "debug.h"
#include <stack>

int kthSmallest(TreeNode *root, int k);

void TestKthSmallest()
{
    TreeNode *node = parse2Tree("[3,1,4,null,2]");
    cout << kthSmallest(node, 2); //2
}

int kthSmallest(TreeNode *root, int k)
{
    stack<TreeNode *> toVisit;
    int visitedCount = 0;
    TreeNode *curr = root;
    while (true)
    {
        while (curr)
        {
            toVisit.push(curr);
            curr = curr->left;
        }
        if (toVisit.empty())
            break;

        curr = toVisit.top();
        toVisit.pop();

        if (++visitedCount == k)
            return curr->val;

        curr = curr->right;
    }

    return -1;
}
