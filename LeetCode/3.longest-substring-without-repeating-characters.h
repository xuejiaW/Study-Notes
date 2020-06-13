// Tags:
// hash-table | two-pointers | string | sliding-window

// Given a string, find the length of the longest substring without repeating characters.

// Example 1:

// Input: "abcabcbb"
// Output: 3 
// Explanation: The answer is "abc", with the length of 3. 
// Example 2:

// Input: "bbbbb"
// Output: 1
// Explanation: The answer is "b", with the length of 1.
// Example 3:

// Input: "pwwkew"
// Output: 3
// Explanation: The answer is "wke", with the length of 3. 
//              Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

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
// times -> O(2n)
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