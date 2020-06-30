#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> parse2Vector_int(string str)
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
