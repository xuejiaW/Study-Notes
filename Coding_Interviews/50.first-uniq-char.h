// 第一个只出现一次的字符

// 难度：简单

// Tags：
// hash-map

// 在字符串 s 中找出第一个只出现一次的字符。如果没有，返回一个单空格。 s 只包含小写字母。

// 示例:

// s = "abaccdeff"
// 返回 "b"

// s = "" 
// 返回 " "

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <algorithm>

using namespace std;

char firstUniqChar(string s);

void TestFirstUnieChar()
{
    // char uniq = firstUniqChar("abaccdeff");
    char uniq = firstUniqChar("leetcode");
    cout << "result is " << uniq << endl;
}

// // Version: using vector and unordered_set
// char firstUniqChar(string s)
// {
//     unordered_set<char> alreadyPaired;
//     vector<char> waitedToPaired;

//     for (int i = 0; i != s.size(); ++i)
//     {
//         if (alreadyPaired.find(s[i]) == alreadyPaired.end())
//         {
//             vector<char>::iterator it = find(waitedToPaired.begin(), waitedToPaired.end(), s[i]);
//             if (it == waitedToPaired.end())
//                 waitedToPaired.push_back(s[i]);
//             else
//             {
//                 alreadyPaired.insert(s[i]);
//                 waitedToPaired.erase(it);
//             }
//         }
//     }

//     char empty = ' ';
//     return waitedToPaired.empty() ? empty : waitedToPaired[0];
// }

// Version: using unordered_map
char firstUniqChar(string s)
{
    unordered_map<char, int> charTimesMap;

    for (auto c : s)
        charTimesMap[c]++;

    for (auto c : s)
    {
        if (charTimesMap[c] == 1)
            return c;
    }

    return ' ';
}
