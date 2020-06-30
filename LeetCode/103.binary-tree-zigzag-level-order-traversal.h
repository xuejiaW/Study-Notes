// 103. 二叉树的锯齿形层次遍历

// 难度：中等

// Tags:

// tree | bfs | dfs

// 给定一个二叉树，返回其节点值的锯齿形层次遍历。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

// 例如：
// 给定二叉树 [3,9,20,null,null,15,7],

//     3
//    / \
//   9  20
//     /  \
//    15   7
// 返回锯齿形层次遍历如下：

// [
//   [3],
//   [20,9],
//   [15,7]
// ]

#include <vector>
#include <queue>
#include "parser.h"
#include "debug.h"

vector<vector<int>> zigzagLevelOrder(TreeNode *root);

void TestBinaryTreeZigzagLevelOrderTraversal()
{
    TreeNode *node = parse2Tree("[3,9,20,null,null,15,7]");
    DebugTree(node);
    auto result = zigzagLevelOrder(node);
    DebugVectorArray(result);
}

// Version: BFS
vector<vector<int>> zigzagLevelOrder(TreeNode *root)
{
    vector<vector<int>> result;
    if (!root)
        return result;

    queue<TreeNode *> toVisit;
    toVisit.push(root);

    bool left2Right = true;
    while (!toVisit.empty())
    {
        int size = toVisit.size();
        deque<int> currLevel;

        for (int i = 0; i != size; ++i)
        {
            TreeNode *temp = toVisit.front();
            toVisit.pop();
            if (left2Right)
                currLevel.push_back(temp->val);
            else
                currLevel.push_front(temp->val);

            if (temp->left)
                toVisit.push(temp->left);
            if (temp->right)
                toVisit.push(temp->right);
        }

        left2Right = !left2Right;
        result.push_back(vector<int>(currLevel.begin(), currLevel.end()));
    }

    return result;
}

// Version: DFS
//TODO
