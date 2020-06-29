// 找到字符串中所有字母异位词

// // Tags:
// // sliding-window

// 给定一个字符串 s 和一个非空字符串 p，找到 s 中所有是 p 的字母异位词的子串，返回这些子串的起始索引。

// 字符串只包含小写英文字母，并且字符串 s 和 p 的长度都不超过 20100。

// 说明：

// 字母异位词指字母相同，但排列不同的字符串。
// 不考虑答案输出的顺序。


// 示例 1:

// 输入:
// s: "cbaebabacd" p: "abc"

// 输出:
// [0, 6]

// 解释:
// 起始索引等于 0 的子串是 "cba", 它是 "abc" 的字母异位词。
// 起始索引等于 6 的子串是 "bac", 它是 "abc" 的字母异位词。
//  示例 2:

// 输入:
// s: "abab" p: "ab"

// 输出:
// [0, 1, 2]

// 解释:
// 起始索引等于 0 的子串是 "ab", 它是 "ab" 的字母异位词。
// 起始索引等于 1 的子串是 "ba", 它是 "ab" 的字母异位词。
// 起始索引等于 2 的子串是 "ab", 它是 "ab" 的字母异位词。


#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> findAnagrams(string s, string p);

void TestFindAnagrams()
{
    string s = "cbaebabacd";
    string p = "abc";
    // string s = "bdbbadeade";
    // string p = "b";
    // string s = "aa";
    // string p = "bb";
    // string s = "aabbc";
    // string p = "c";

    vector<int> result = findAnagrams(s, p);
    cout << "result is " << result.size() << endl;
    for (int i : result)
        cout << i << endl;
}

// // Version: using brute solution
// vector<int> findAnagrams(string s, string p)
// {
//     vector<int> result;
//     int sLength = s.length(), pLength = p.length(), lastPossibleIndex = sLength - pLength;

//     int includeIndex = s.find_first_of(p);
//     int notIncludeIndex = s.find_first_not_of(p);
//     int xorResult = 0;

//     while (includeIndex != -1)
//     {
//         while (includeIndex > notIncludeIndex && notIncludeIndex != -1)
//             notIncludeIndex = s.find_first_not_of(p, notIncludeIndex + 1);

//         if ((notIncludeIndex == -1 || includeIndex <= notIncludeIndex - pLength) && includeIndex + pLength <= sLength)
//         {
//             xorResult = 0;
//             for (int j = 0; j != pLength; ++j)
//             {
//                 xorResult ^= s[includeIndex + j];
//                 xorResult ^= p[j];
//             }
//             if (xorResult == 0)
//                 result.push_back(includeIndex);
//         }
//         includeIndex = s.find_first_of(p, includeIndex + 1);
//     }

//     return result;
// }

// Version: sliding-window
vector<int> findAnagrams(string s, string p)
{
    vector<int> result;
    vector<int> goals(26), curr(26);
    for (char pChar : p)
        goals[pChar - 'a']++;

    int sLength = s.length(), pLength = p.length();

    for (int i = 0; i != sLength; ++i)
    {
        curr[s[i] - 'a']++;

        if (i >= pLength) //need to handle window's left side
            curr[s[i - pLength] - 'a']--;

        if (goals == curr)
            result.push_back(i - pLength + 1);
    }
    return result;
}
