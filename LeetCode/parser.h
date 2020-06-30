#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> parse2Vector(string str)
{
    vector<int> result;
    str = str.substr(1, str.size() - 2);
    int pos = 0;
    while ((pos = str.find(',')) != -1)
    {
        string sub = str.substr(0, pos);
        result.push_back(stoi(str.substr(0, pos)));
        str.erase(0, pos + 1);
    }
    result.push_back(stoi(str));

    return result;
}

vector<vector<int>> parser2VectorArray(string str)
{
    vector<vector<int>> result;
    str = str.substr(1, str.size() - 2);
    int pos = 0;
    while ((pos = str.find(",[")) != -1)
    {
        string sub = str.substr(0, pos);
        result.push_back(parse2Vector(sub));
        str.erase(0, pos + 1);
    }

    result.push_back(parse2Vector(str));
    return result;
}
