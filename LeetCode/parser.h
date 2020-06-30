#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> parse2Vector(string str)
{
    vector<int> result;
    int sSize = str.size();
    str = str.substr(1, sSize - 2);
    int pos = 0;
    while ((pos = str.find(',')) != -1)
    {
        result.push_back(stoi(str.substr(0, pos)));
        str.erase(0, pos + 1);
    }
    result.push_back(stoi(str));

    return result;
}

// vector<vector<int>> 
