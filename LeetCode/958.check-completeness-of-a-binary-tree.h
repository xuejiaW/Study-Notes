// 二叉树的完全性检验

// 难度：中等

// Tags
// array | breadth-first-search

// 给定一个二叉树，确定它是否是一个完全二叉树。

// 百度百科中对完全二叉树的定义如下：

// 若设二叉树的深度为 h，除第 h 层外，其它各层 (1～h-1) 的结点数都达到最大个数，第 h 层所有的结点都连续集中在最左边，这就是完全二叉树。（注：第 h 层可能包含 1~ 2h 个节点。）

// 输入：[1,2,3,4,5,6]
// 输出：true
// 解释：最后一层前的每一层都是满的（即，结点值为 {1} 和 {2,3} 的两层），且最后一层中的所有结点（{4,5,6}）都尽可能地向左。

// 示例 2：

// 输入：[1,2,3,4,5,null,7]
// 输出：false
// 解释：值为 7 的结点没有尽可能靠向左侧。

#include "parser.h"
#include "debug.h"

bool isCompleteTree(TreeNode *root);
void TestIsCompleteTree()
{
    // TreeNode *root = parse2Tree("[1,2,3,4,5,6]");
    TreeNode *root = parse2Tree("[1,2,3,4,5,null,7]");
    cout << isCompleteTree(root);
}

bool isCompleteTree(TreeNode *root)
{
    if (!root)
        return true;
    queue<TreeNode *> toVisit;
    toVisit.push(root);

    bool meetNull = false;
    while (!toVisit.empty())
    {
        TreeNode *curr = toVisit.front();
        toVisit.pop();
        if (curr != NULL && meetNull)
            return false;
        if (curr == NULL)
        {
            meetNull = true;
        }
        else
        {
            toVisit.push(curr->left);
            toVisit.push(curr->right);
        }
    }
    return true;
}
