// 从上到下打印二叉树 III

// 难度：中等

// Tags:

// tree | breadth-first-searching

// 请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。

//  

// 例如:
// 给定二叉树: [3,9,20,null,null,15,7],

//     3
//    / \
//   9  20
//     /  \
//    15   7
// 返回其层次遍历结果：

// [
//   [3],
//   [20,9],
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


// Version: 
vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> result;

    if (!root)
        return result;

    queue<TreeNode *> toVisit;
    toVisit.push(root);

    int currLevel = 0;

    while (!toVisit.empty())
    {
        int currLevelNum = toVisit.size();
        result.push_back(vector<int>());

        vector<int> temp;
        for (int i = 0; i != currLevelNum; ++i)
        {
            TreeNode *curr = toVisit.front();
            toVisit.pop();

            temp.push_back(curr->val);

            if (curr->left)
                toVisit.push(curr->left);
            if (curr->right)
                toVisit.push(curr->right);
        }

        if (currLevel % 2 == 1)
            result.back().insert(result.back().end(), temp.rbegin(), temp.rend());
        else
            result.back().insert(result.back().end(), temp.begin(), temp.end());

        currLevel++;
    }

    return result;
}
