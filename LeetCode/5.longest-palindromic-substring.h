// 5. 最长回文子串

// 难度：中等

// Tags:
// dynamic programming

// 给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

// 示例 1：

// 输入: "babad"
// 输出: "bab"
// 注意: "aba" 也是一个有效答案。
// 示例 2：

// 输入: "cbbd"
// 输出: "bb"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

string longestPalindrome(string s);
void TestLongestPalindrome()
{
    string result = longestPalindrome("cbbbbdaaa");
    cout << "result is " << result << endl;
}

// // Version: expanding
// pair<int, int> expandPalindrome(string &s, int left, int right);
// string longestPalindrome(string s)
// {
//     int sSize = s.size();
//     int start = 0, end = 0;
//     for (int i = 0; i != sSize; ++i)
//     {
//         auto [left1, right1] = expandPalindrome(s, i, i);// the palindrome is odd
//         auto [left2, right2] = expandPalindrome(s, i, i + 1);// the palindrom is even
//         if ((right1 - left1) > (end - start))
//         {
//             end = right1;
//             start = left1;
//         }

//         if ((right2 - left2) > (end - start))
//         {
//             end = right2;
//             start = left2;
//         }
//     }

//     return s.substr(start, end - start + 1);
// }

// pair<int, int> expandPalindrome(string &s, int left, int right)
// {
//     int sSize = s.size();
//     while (left >= 0 && right <= sSize - 1 && s[left] == s[right])
//     {
//         --left;
//         ++right;
//     }

//     return {left + 1, right - 1};
// }

// Version: dynamic programming
// f[i][j] = f[i+1][j+1] && s[i]==s[j]
string longestPalindrome(string s)
{
    int sSize = s.length();
    vector<vector<int>> dpArr = vector<vector<int>>(sSize, vector<int>(sSize)); // two-dimensional array

    string result = "";

    for (int gap = 0; gap != sSize; ++gap)
    {
        for (int i = 0; (i + gap) != sSize; ++i)
        {
            int j = i + gap;
            if (gap == 0)
                dpArr[i][j] = 1;
            else if (gap == 1 && s[i] == s[j])
                dpArr[i][j] = 1;
            else if (s[i] == s[j] && dpArr[i + 1][j - 1])
                dpArr[i][j] = 1;

            if (dpArr[i][j] && (gap + 1) > result.size())
                result = s.substr(i, gap + 1);
        }
    }

    return result;
}
