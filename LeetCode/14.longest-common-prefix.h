// 最长公共前缀

// 难度：简单

// Tags
// string

// 编写一个函数来查找字符串数组中的最长公共前缀。

// 如果不存在公共前缀，返回空字符串 ""。

// 示例 1:

// 输入: ["flower","flow","flight"]
// 输出: "fl"
// 示例 2:

// 输入: ["dog","racecar","car"]
// 输出: ""
// 解释: 输入不存在公共前缀。
// 说明:

// 所有输入只包含小写字母 a-z 。

#include <vector>
#include <string>
#include <iostream>

using namespace std;

string longestCommonPrefix(vector<string> &strs);

void TestLongestCommonPrefix()
{
    // vector<string> strs{"flower", "flow", "flight"};
    // vector<string> strs{"dog", "racecar", "car"};
    vector<string> strs{""};

    string result = longestCommonPrefix(strs);
    cout << result << endl;
}

string longestCommonPrefix(vector<string> &strs)
{
    string result;

    if (strs.empty())
        return result;

    int strsSize = strs.size();
    if (strsSize == 1)
        return strs[0];

    int digit = 0;
    while (true)
    {
        bool broken = false;
        for (int i = 1; i != strsSize; ++i)
        {
            if (digit >= strs[i - 1].length() || digit >= strs[i].length() || strs[i][digit] != strs[i - 1][digit])
            {
                broken = true;
                break;
            }
            if (i == (strsSize - 1))
                result.push_back(strs[i][digit]);
        }
        if (broken)
            break;
        else
            digit++;
    }
    return result;
}
