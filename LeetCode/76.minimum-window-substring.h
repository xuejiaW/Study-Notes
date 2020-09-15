// 76. 最小覆盖子串

// 难度：困难

// Tags: hash-table, two-pointer, string, sliding-window

// 给你一个字符串 S、一个字符串 T 。请你设计一种算法，可以在 O(n) 的时间复杂度内，从字符串 S 里面找出：包含 T 所有字符的最小子串。

// 示例：

// 输入：S = "ADOBECODEBANC", T = "ABC"
// 输出："BANC"
//  

// 提示：

// 如果 S 中不存这样的子串，则返回空字符串 ""。
// 如果 S 中存在这样的子串，我们保证它是唯一的答案。

#include "parser.h"
#include "debug.h"
#include <unordered_map>
#include <climits>
using namespace std;

// #include <string>
// #include <iostream>
// #include <vector>

string minWindow(string s, string t);

void TestMinWindow()
{
    string result = minWindow("ADOBECODEBANC", "ABC");
    // string result = minWindow("a", "c");
    // string result = minWindow("cabwefgewcwaefgcf", "cae");
    cout << "result is " << result << endl;
}

//
bool contains(vector<int> &target, vector<int> &container)
{
    int baseSize = target.size();
    for (int i = 0; i != baseSize; ++i)
    {
        if (target[i] != 0 && target[i] > container[i])
            return false;
    }

    return true;
}

string minWindow(string s, string t)
{
    int sSize = s.size(), tSize = t.size();
    if (sSize == 0 || sSize < tSize)
        return "";

    vector<int> tMap(58, 0);
    vector<int> windowMap(58, 0);

    for (const char &ch : t)
        tMap[ch - 'A']++;

    int minLength = INT_MAX, start = 0;

    int left = 0, right = 0;
    while (right != sSize)
    {
        windowMap[s[right] - 'A']++;

        while (left <= right && contains(tMap, windowMap))
        {
            if ((right - left + 1) < minLength)
            {
                minLength = right - left + 1;
                start = left;
            }

            windowMap[s[left] - 'A']--;
            left++;
        }
        right++;
    }

    return minLength == INT_MAX ? "" : s.substr(start, minLength);
}

// Version: optimization
string minWindow(string s, string t)
{
    vector<int> tMap(58, 0);
    for (const char &c : t)
        tMap[c - 'A']++;

    int matchedCount = 0;
    int minLength = INT_MAX;
    int left = 0, right = 0, begin = 0;
    while (right != s.size())
    {
        if (--tMap[s[right] - 'A'] >= 0)
            matchedCount++;
        while (left <= right && matchedCount == t.size())
        {
            if (minLength > (right - left + 1))
            {
                begin = left;
                minLength = right - left + 1;
            }
            if (++tMap[s[left] - 'A'] > 0)
                matchedCount--;
            left++;
        }
        right++;
    }

    return minLength == INT_MAX ? "" : s.substr(begin, minLength);
}
