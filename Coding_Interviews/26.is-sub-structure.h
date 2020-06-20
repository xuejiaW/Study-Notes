// 树的子结构

// 难度：中等

// Tags:

// tree

// 输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)

// B是A的子结构， 即 A中有出现和B相同的结构和节点值。

// 例如:
// 给定的树 A:

//      3
//     / \
//    4   5
//   / \
//  1   2
// 给定的树 B：

//    4 
//   /
//  1
// 返回 true，因为 B 与 A 的一个子树拥有相同的结构和节点值。

// 示例 1：

// 输入：A = [1,2,3], B = [3,1]
// 输出：false
// 示例 2：

// 输入：A = [3,4,5,1,2], B = [4,1]
// 输出：true


#include <vector>
#include <iostream>
#include <stack>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool isSubStructure(TreeNode *A, TreeNode *B);

void TestIsSubStructure()
{
    TreeNode *aTree = new TreeNode(3);
    TreeNode *aLeft = new TreeNode(4);
    aLeft->left = new TreeNode(1);
    aLeft->right = new TreeNode(2);
    aTree->left = aLeft;
    aTree->right = new TreeNode(5);

    TreeNode *bTree = new TreeNode(3);
    bTree->right = new TreeNode(4);

    bool result = isSubStructure(aTree, bTree);
    cout << "result is " << result << endl;
}

// 通过比较遍历的结果行不通，因为有左右子树空缺的情况，所以相邻的节点在遍历结果中并不一定相邻（无论是什么遍历方式）

bool helper(TreeNode *A, TreeNode *B);

bool isSubStructure(TreeNode *A, TreeNode *B)
{
    return (A != nullptr && B != nullptr) && (helper(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B));
}

bool helper(TreeNode *A, TreeNode *B)
{
    if (B == nullptr)
        return true;
    if (A == nullptr || A->val != B->val)
        return false;
    return helper(A->left, B->left) && helper(A->right, B->right);
}