#include "parser.h"
#include "debug.h"
#include <stack>

bool isValidBST(TreeNode *root);

void TestIsValidBST()
{
    TreeNode *root = parse2Tree("[5,1,4,null,null,3,6]");
    // TreeNode *root = parse2Tree("[2,1,3]");
    // TreeNode *root = parse2Tree("[5,4,7,2,null,6,null]");
    bool result = isValidBST(root);
    cout << result << endl;
}

// bool helper(TreeNode *root, long long minLimit, long long maxLimit);
// bool isValidBST(TreeNode *root)
// {
//     return helper(root, LONG_MIN, LONG_MAX);
// }

// bool helper(TreeNode *root, long long minLimit, long long maxLimit)
// {
//     if (!root)
//         return true;
//     if (root->val <= minLimit || root->val >= maxLimit)
//         return false;
//     return helper(root->left, minLimit, root->val) && helper(root->right, root->val, maxLimit);
// }

// Version: inorder
bool isValidBST(TreeNode *root)
{
    if (!root)
        return true;

    long long lastVal = LONG_MIN;
    stack<TreeNode *> toVisit;
    TreeNode *curr = root;

    while (true)
    {
        while (curr)
        {
            toVisit.push(curr);
            curr = curr->left;
        }

        if (toVisit.empty())
        {
            break;
        }

        curr = toVisit.top();
        toVisit.pop();

        if (curr->val > lastVal)
            lastVal = curr->val;
        else
            return false;

        curr = curr->right;
    }

    return true;
}