// 平衡二叉树

// 难度：简单

// Tags:
// tree | depth-first-search | breadth-first-search

// 给定一个二叉树，判断它是否是高度平衡的二叉树。

// 本题中，一棵高度平衡二叉树定义为：

// 一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1。

// 示例 1:

// 给定二叉树 [3,9,20,null,null,15,7]

//     3
//    / \
//   9  20
//     /  \
//    15   7
// 返回 true 。

// 示例 2:

// 给定二叉树 [1,2,2,3,3,null,null,4,4]

//        1
//       / \
//      2   2
//     / \
//    3   3
//   / \
//  4   4
// 返回 false 。

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

bool isBalanced(TreeNode *root);
void TestBalanced()
{
    TreeNode *tree3 = new TreeNode(3);
    TreeNode *tree2 = new TreeNode(2, tree3, nullptr);
    TreeNode *tree1 = new TreeNode(1, nullptr, tree2);

    bool result = isBalanced(tree1);
    cout << "result is " << result << endl;
}

// // Version: using getDepth from up to bottom (containing lots of duplicated operation)
// int getDepth(TreeNode *root);
// bool isBalanced(TreeNode *root)
// {
//     if (!root)
//         return true;
//     return isBalanced(root->left) &&  // left match
//            isBalanced(root->right) && //right match
//            abs(getDepth(root->left) - getDepth(root->right)) <= 1;
// }

// int getDepth(TreeNode *root)
// {
//     if (!root)
//         return 0;
//     return max(getDepth(root->left), getDepth(root->right)) + 1;
// }

// // Version: using getDepeth from bottom to up
bool isBalanced(TreeNode *root)
{
    return getDepth(root) != -1;
}

int getDepth(TreeNode *root)
{
    //-1 mean this tree is not balanced

    if (!root)
        return 0;

    int left = getDepth(root->left);
    if (left == -1)
        return -1;

    int right = getDepth(root->right);
    if (right == -1)
        return -1;

    return abs(left - right) <= 1 ? max(left, right) + 1 : -1;
}
