// 二叉搜索树的后序遍历序列

// 难度：中等

// Tags:

// divide and conquer

// 输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。如果是则返回 true，否则返回 false。假设输入的数组的任意两个数字都互不相同。

//  

// 参考以下这颗二叉搜索树：

//      5
//     / \
//    2   6
//   / \
//  1   3
// 示例 1：

// 输入: [1,6,3,2,5]
// 输出: false
// 示例 2：

// 输入: [1,3,2,6,5]
// 输出: true

#include <iostream>
#include <vector>

using namespace std;

bool verifyPostorder(vector<int> &postorder);

void TestVerifyPoster()
{
    vector<int> postorder{4, 8, 6, 12, 16, 14, 10};
    bool result = verifyPostorder(postorder);
    cout << result << endl;
}

bool verifyPostorder(vector<int> &postorder)
{
    if (postorder.empty())
        return true;

    int headValue = postorder.back();
    int rightIndex = postorder.size() - 1;

    // the first element larger than the head should be the head of the right tree
    for (int i = 0; i != postorder.size(); ++i)
    {
        if (postorder[i] > headValue)
        {
            rightIndex = i;
            break;
        }
    }

    // check for the current tree, all nodes in right tree should larger than headValue
    for (int i = rightIndex + 1; i != postorder.size(); ++i)
    {
        if (postorder[i] < headValue)
            return false;
    }

    vector<int> left = vector<int>(postorder.begin(), postorder.begin() + rightIndex);
    vector<int> right = vector<int>(postorder.begin() + rightIndex, postorder.end() - 1);

    return verifyPostorder(left) && verifyPostorder(right);
}