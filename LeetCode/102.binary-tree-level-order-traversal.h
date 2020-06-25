// 二叉树的层序遍历

// 难度：中等

// Tags:
// Tree | Breadth-first-searchin

// 给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。

//  

// 示例：
// 二叉树：[3,9,20,null,null,15,7],

//     3
//    / \
//   9  20
//     /  \
//    15   7
// 返回其层次遍历结果：

// [
//   [3],
//   [9,20],
//   [15,7]
// ]

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

vector<vector<int>> levelOrder(TreeNode *root);

void TestLevelOrderTraval()
{
    TreeNode *tree20 = new TreeNode(20, new TreeNode(15), new TreeNode(7));
    TreeNode *tree9 = new TreeNode(9, new TreeNode(10), nullptr);
    TreeNode *tree3 = new TreeNode(3, tree9, tree20);

    vector<vector<int>> result = levelOrder(tree3);
    for (vector<int> vec : result)
    {
        for (int i : vec)
            cout << i << " ";
        cout << endl;
    }
}

// // Version: manually count next level num and current level num
// vector<vector<int>> levelOrder(TreeNode *root)
// {
//     vector<vector<int>> result;

//     if (!root)
//         return result;

//     queue<TreeNode *> toVisit;
//     int nextLevelNum = 0, currLevelNum = 1, currVisit = 0;

//     result.push_back(vector<int>());
//     toVisit.push(root);

//     TreeNode *curr = nullptr;
//     while (!toVisit.empty())
//     {
//         if (currVisit == currLevelNum) // one level completed
//         {
//             currVisit = 0;
//             currLevelNum = nextLevelNum;
//             nextLevelNum = 0;
//             result.push_back(vector<int>());
//         }

//         curr = toVisit.front();
//         toVisit.pop();

//         result.back().push_back(curr->val);

//         if (curr->left)
//         {
//             nextLevelNum++;
//             toVisit.push(curr->left);
//         }
//         if (curr->right)
//         {
//             nextLevelNum++;
//             toVisit.push(curr->right);
//         }

//         currVisit++;
//     }

//     return result;
// }

// Version: use inline loop to calculate one level
vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> result;
    if (!root)
        return result;

    queue<TreeNode *> toVisit;

    toVisit.push(root);

    TreeNode *curr = nullptr;

    while (!toVisit.empty())
    {
        int currLevel = toVisit.size();
        result.push_back(vector<int>());

        for (int i = 0; i != currLevel; ++i)
        {
            curr = toVisit.front();
            toVisit.pop();
            result.back().push_back(curr->val);

            if (curr->left)
                toVisit.push(curr->left);
            if (curr->right)
                toVisit.push(curr->right);
        }
    }
    return result;
}
