#pragma once

#include <iostream>
#include <vector>

using namespace std;

void DebugIntVector(vector<int> vec)
{
    for (auto i : vec)
        cout << i << endl;
}

void DebugIntVectorArray(vector<vector<int>> vecArray)
{
    for (auto vec : vecArray)
    {
        for (auto i : vec)
            cout << i << " ";
        cout << endl;
    }
}