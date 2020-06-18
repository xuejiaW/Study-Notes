// Tags:
// array | tree

// Given preorder and inorder traversal of a tree, construct the binary tree.

// Note:
// You may assume that duplicates do not exist in the tree.

// For example, given

// preorder = [3,9,20,15,7]
// inorder = [9,3,15,20,7]
// Return the following binary tree:

//     3
//    / \
//   9  20
//     /  \
//    15   7


#include <vector>
#include <iostream>
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

TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder);

void TestBuildTree()
{
    vector<int> preorder{3, 9, 20, 15, 7};
    vector<int> inorder{9, 3, 15, 20, 7};
    TreeNode *result = buildTree(preorder, inorder);
    cout << "head is " << result->val << endl;
    cout << "left is " << result->left->val << endl;
    cout << "right is " << result->right->val << endl;
}

TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder, unordered_map<int, int> &indexMap,
                    int preStart, int preEnd, int inStart, int inEnd);
TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
{
    unordered_map<int, int> valueIndexMap;
    for (int i = 0; i != inorder.size(); ++i)
        valueIndexMap[inorder[i]] = i;
    return buildTree(preorder, inorder, valueIndexMap, 0, preorder.size() - 1, 0, inorder.size() - 1);
}

TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder, unordered_map<int, int> &indexMap,
                    int preStart, int preEnd, int inStart, int inEnd)
{
    if (preStart > preEnd || inStart > inEnd)
        return nullptr;

    TreeNode *node = new TreeNode(preorder[preStart]);
    int headIndex_inorder = indexMap[preorder[preStart]];

    int leftNodeNum = headIndex_inorder - inStart;
    int rightNodeNum = inEnd - headIndex_inorder;

    node->left = buildTree(preorder, inorder, indexMap, preStart + 1, preStart + leftNodeNum, inStart, inStart + leftNodeNum - 1);
    node->right = buildTree(preorder, inorder, indexMap, preEnd - rightNodeNum + 1, preEnd, inEnd - rightNodeNum + 1, inEnd);
    return node;
}
