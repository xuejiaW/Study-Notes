#pragma once

#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include "treeNode.h"

using namespace std;

vector<int> parse2Vector_int(string str)
{
    vector<int> result;
    str = str.substr(1, str.size() - 2);
    int pos = 0;
    while ((pos = str.find(',')) != -1)
    {
        result.push_back(stoi(str.substr(0, pos)));
        str.erase(0, pos + 1);
    }
    result.push_back(stoi(str));

    return result;
}

vector<vector<int>> parser2VectorArray_int(string str)
{
    vector<vector<int>> result;
    str = str.substr(1, str.size() - 2);
    int pos = 0;
    while ((pos = str.find(",[")) != -1)
    {
        string sub = str.substr(0, pos);
        result.push_back(parse2Vector_int(sub));
        str.erase(0, pos + 1);
    }

    result.push_back(parse2Vector_int(str));
    return result;
}

vector<char> parse2Vector_char(string str)
{
    vector<char> result;
    for (const char &c : str)
        result.push_back(c);

    return result;
}

vector<vector<char>> parser2VectorArray_char(string str)
{
    vector<vector<char>> result;
    int pos = 0;
    while ((pos = str.find(",")) != -1)
    {
        string sub = str.substr(0, pos);
        cout << "sub is " << sub << endl;
        result.push_back(parse2Vector_char(sub));
        str.erase(0, pos + 1);
    }

    result.push_back(parse2Vector_char(str));
    return result;
}

TreeNode *parser2Tree(string str)
{
    TreeNode *head = nullptr;
    queue<TreeNode *> headNodeQuque;
    int currNode = -1; // 1 for left, 2 for right    // cout << "after debug" << endl;

    str = str.substr(1, str.size() - 2);
    int pos = 0;

    while ((pos = str.find(',')) != -1)
    {
        string temp = str.substr(0, pos);

        if (head == nullptr)
        {
            head = new TreeNode(stoi(temp));
            headNodeQuque.push(head);
            currNode = 1;
        }
        else if (!headNodeQuque.empty())
        {
            TreeNode *tempHead = headNodeQuque.front();
            if (currNode == 1)
            {
                if (temp != "null")
                {
                    tempHead->left = new TreeNode(stoi(temp));
                    headNodeQuque.push(head->left);
                }
                currNode = 2;
            }
            else if (currNode == 2)
            {
                if (temp != "null")
                {
                    tempHead->right = new TreeNode(stoi(temp));
                    headNodeQuque.push(head->right);
                }
                currNode = 1;
                headNodeQuque.pop();
            }
        }

        str.erase(0, pos + 1);
    }

    if (!headNodeQuque.empty())
    {
        if (str != "null")
        {
            TreeNode *tempHead = headNodeQuque.front();
            TreeNode *temp = new TreeNode(stoi(str));
            if (currNode == 1)
                tempHead->left = temp;
            else if (currNode == 2)
                tempHead->right = temp;
        }
    }

    return head;
}
