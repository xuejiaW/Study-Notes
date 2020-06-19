// 无重复字符的最长子串

// 难度：中等

// Tags:
// hash-table | two-pointers | string | sliding-window

// 给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

// 示例 1:

// 输入: "abcabcbb"
// 输出: 3 
// 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
// 示例 2:

// 输入: "bbbbb"
// 输出: 1
// 解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
// 示例 3:

// 输入: "pwwkew"
// 输出: 3
// 解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
//      请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int lengthOfLongestSubstring(string s);

void TestLengthofLonggestSubstring()
{
    string s = "abcabcbb";
    // string s = "bbbbb";
    // string s = "pwwkew";
    // string s = "ddabcde";
    // string s = " ";
    // string s = "abba";
    // string s = "abcdcabefg";
    int result = lengthOfLongestSubstring(s);
    cout << result << endl;
}

// // Version: sliding window with unordered_set
// int lengthOfLongestSubstring(string s)
// {
//     unordered_set<char> charSet;
//     int first = 0, sec = 0, result = 0, num = s.size();

//     while (sec < num)
//     {
//         if (charSet.find(s[sec]) == charSet.end())
//         {
//             charSet.insert(s[sec++]);
//             result = max(result, sec - first);
//         }
//         else
//         {
//             charSet.erase(s[first++]);
//         }
//     }
//     return result;
// }

// // Version: sliding window with unordered_map to reduce moving operation
// int lengthOfLongestSubstring(string s)
// {
//     unordered_map<char, int> charIndexMap;

//     int first = 0, sec = 0, num = s.size(), result = 0;

//     while (sec != num)
//     {
//         if (charIndexMap.find(s[sec]) == charIndexMap.end() || charIndexMap[s[sec]] == sec)
//         {
//             charIndexMap[s[sec]] = sec;
//             result = max(result, ++sec - first);
//         }
//         else
//         {
//             first = max(first, charIndexMap[s[sec]] + 1);
//             charIndexMap[s[sec]] = sec;
//         }
//     }
//     return result;
// }

// Version: because the key is char so can use character array
int lengthOfLongestSubstring(string s)
{
    int charIndexMap[256];
    for (int &i : charIndexMap)
        i = -1;

    int first = 0, sec = 0, num = s.size(), result = 0;

    while (sec != num)
    {
        if (charIndexMap[s[sec]] == -1 || charIndexMap[s[sec]] == sec)
        {
            charIndexMap[s[sec]] = sec;
            result = max(result, ++sec - first);
        }
        else
        {
            first = max(first, charIndexMap[s[sec]] + 1);
            charIndexMap[s[sec]] = sec;
        }
    }
    return result;
}