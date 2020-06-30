#pragma once

#include <iostream>
#include <vector>

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