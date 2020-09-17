//  [108] 将有序数组转换为二叉搜索树

// Tags
// tree | depth-first-search
 
//   https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/description/
 
//   Easy
 
//   将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树。
  
//   本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。
  
//   示例:
  
//   给定有序数组: [-10,-3,0,5,9],
  
//   一个可能的答案是：[0,-3,9,-10,null,5]，它可以表示下面这个高度平衡二叉搜索树：
  
//   ⁠     0
//   ⁠    / \
//   ⁠  -3   9
//   ⁠  /   /
//   ⁠-10  5
  
  

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include "parser.h"
#include "debug.h"

TreeNode *sortedArrayToBST(vector<int> &nums);
void TestSortedArrayToBST()
{
    vector<int> nums = {-10, -3, 0, 5, 9};
    TreeNode *root = sortedArrayToBST(nums);
    cout << "end" << endl;
    DebugTree(root);
}

TreeNode *sortedArrayToBST(vector<int> &nums, int begin, int end)
{
    if (begin > end)
        return nullptr;

    if (begin == end)
        return new TreeNode(nums[begin]);

    int mid = (begin + end + 1) / 2; // if the count is even, choose the mid right

    TreeNode *root = new TreeNode(nums[mid]);
    root->left = sortedArrayToBST(nums, begin, mid - 1);
    root->right = sortedArrayToBST(nums, mid + 1, end);
    return root;
}

TreeNode *sortedArrayToBST(vector<int> &nums)
{
    int numsCount = nums.size();
    if (numsCount == 0)
        return nullptr;
    return sortedArrayToBST(nums, 0, numsCount - 1);
}
