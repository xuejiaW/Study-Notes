// Tags:
// sliding-window

// Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

// Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

// The order of output does not matter.

// Example 1:

// Input:
// s: "cbaebabacd" p: "abc"

// Output:
// [0, 6]

// Explanation:
// The substring with start index = 0 is "cba", which is an anagram of "abc".
// The substring with start index = 6 is "bac", which is an anagram of "abc".
// Example 2:

// Input:
// s: "abab" p: "ab"

// Output:
// [0, 1, 2]

// Explanation:
// The substring with start index = 0 is "ab", which is an anagram of "ab".
// The substring with start index = 1 is "ba", which is an anagram of "ab".
// The substring with start index = 2 is "ab", which is an anagram of "ab".

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
