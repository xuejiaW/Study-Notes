#pragma once

#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "TreeNode.h"
#include "ListNode.h"

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
        // cout << "sub is " << sub << endl;
        result.push_back(parse2Vector_char(sub));
        str.erase(0, pos + 1);
    }

    result.push_back(parse2Vector_char(str));
    return result;
}

TreeNode *parse2Tree(string str)
{
    str = str.substr(1, str.size() - 2); // erase [ and ]
    int pos = 0;
    queue<string> strQueue;

    while ((pos = str.find(',')) != -1)
    {
        string temp = str.substr(0, pos);
        strQueue.push(temp);
        str.erase(0, pos + 1);
    }
    strQueue.push(str);

    if (strQueue.empty())
        return nullptr;

    TreeNode *head = new TreeNode(stoi(strQueue.front()));
    strQueue.pop();

    vector<TreeNode *> lastLevelNodes;
    lastLevelNodes.push_back(head);

    int currLevel = 1;

    while (!strQueue.empty())
    {
        vector<TreeNode *> currentLevelNodes;
        int targetNum = pow(2, (currLevel++));

        for (int i = 0; i != targetNum; ++i)
        {
            if (strQueue.empty())
                break;
            string str = strQueue.front();
            strQueue.pop();
            TreeNode *head = lastLevelNodes[i / 2];
            if (str == "null")
                currentLevelNodes.push_back(nullptr);
            else
            {
                TreeNode *n = new TreeNode(stoi(str));
                currentLevelNodes.push_back(n);
                i % 2 == 0 ? head->left = n : head->right = n;
            }
        }
        lastLevelNodes = currentLevelNodes;
    }

    return head;
}

ListNode *parse2List(string str)
{
    ListNode *headPrev = new ListNode(-1);
    ListNode *headPrevTemp = headPrev;
    str = str.substr(1, str.size() - 2);
    int pos = 0;
    while ((pos = str.find(',')) != -1)
    {
        headPrevTemp->next = new ListNode(stoi(str.substr(0, pos)));
        str.erase(0, pos + 1);
        headPrevTemp = headPrevTemp->next;
    }
    headPrevTemp->next = new ListNode(stoi(str));

    return headPrev->next;
}
