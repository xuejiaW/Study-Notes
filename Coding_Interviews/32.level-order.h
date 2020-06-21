// 从上到下打印二叉树

// 难度：中等

// Tags:
// Tree | Breadth-first-searching

// 从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。

//  

// 例如:
// 给定二叉树: [3,9,20,null,null,15,7],

//     3
//    / \
//   9  20
//     /  \
//    15   7
// 返回：

// [3,9,20,15,7]

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

vector<int> levelOrder(TreeNode *root);

void TestLevelOrderTraval()
{
    TreeNode *tree20 = new TreeNode(20, new TreeNode(15), new TreeNode(7));
    TreeNode *tree9 = new TreeNode(9, nullptr, nullptr);
    TreeNode *tree3 = new TreeNode(3, tree9, tree20);

    vector<int> result = levelOrder(tree3);
    for (int i : result)
        cout << i << endl;
}

vector<int> levelOrder(TreeNode *root)
{
    vector<int> result;
    if (!root)
        return result;

    queue<TreeNode *> toVisit;
    toVisit.push(root);

    TreeNode *curr = nullptr;
    while (!toVisit.empty())
    {
        curr = toVisit.front();
        toVisit.pop();
        result.push_back(curr->val);

        if (curr->left)
            toVisit.push(curr->left);
        if (curr->right)
            toVisit.push(curr->right);
    }

    return result;
}