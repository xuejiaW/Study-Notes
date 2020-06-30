#pragma once

#include <iostream>
#include <vector>
#include "parser.h"

using namespace std;

template <typename T>
void DebugVector(vector<T> vec)
{
    for (auto i : vec)
        cout << i << endl;
}

template <typename T>
void DebugVectorArray(vector<vector<T>> vecArray)
{
    for (auto vec : vecArray)
    {
        for (auto i : vec)
            cout << i << " ";
        cout << endl;
    }
}

void DebugTree(TreeNode *head)
{
    queue<TreeNode *> toVisit;
    toVisit.push(head);
    while (!toVisit.empty())
    {
        int size = toVisit.size();
        for (int i = 0; i != size; ++i)
        {
            TreeNode *curr = toVisit.front();
            toVisit.pop();
            if (!curr)
            {
                cout << "null ";
                continue;
            }
            else
            {
                cout << curr->val << " ";
                toVisit.push(curr->left);
                toVisit.push(curr->right);
            }
        }
        cout << endl;
    }
}