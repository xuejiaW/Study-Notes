// 字符串的排列

// 难度：中等

// Tag：

// back tracking

// 输入一个字符串，打印出该字符串中字符的所有排列。

//  

// 你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。

//  

// 示例:

// 输入：s = "abc"
// 输出：["abc","acb","bac","bca","cab","cba"]

#include <iostream>
#include <vector>
#include <unordered_set>
#include <iterator>

using namespace std;

vector<string> permutation(string s);

void TestPermutation()
{
    vector<string> result = permutation("abc");
    for (string i : result)
        cout << i << " " << endl;
}

void GetPermutationWhenFixIndex(unordered_set<string> &result, string &originStr, int fixedIndex);
vector<string> permutation(string s)
{
    unordered_set<string> resultSet;
    GetPermutationWhenFixIndex(resultSet, s, 0);
    return vector<string>(resultSet.begin(), resultSet.end());
}

void GetPermutationWhenFixIndex(unordered_set<string> &result, string &str, int fixedIndex)
{
    if (fixedIndex == str.length())
    {
        result.insert(str);
        return;
    }

    for (int i = fixedIndex; i != str.length(); i++)
    {
        swap(str[fixedIndex], str[i]); // change the fixed char
        GetPermutationWhenFixIndex(result, str, fixedIndex + 1);
        swap(str[fixedIndex], str[i]); // recover the origin char for the next calculation
    }
}