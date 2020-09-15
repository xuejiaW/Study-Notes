//  [91] 解码方法

//  Tags: string, dynamic programming

//  https://leetcode-cn.com/problems/decode-ways/description/

//  Medium (24.48%)

//  一条包含字母 A-Z 的消息通过以下方式进行了编码：

//  'A' -> 1
//  'B' -> 2
//  ...
//  'Z' -> 26


//  给定一个只包含数字的非空字符串，请计算解码方法的总数。

//  示例 1:

//  输入: "12"
//  输出: 2
//  解释: 它可以解码为 "AB"（1 2）或者 "L"（12）。


//  示例 2:

//  输入: "226"
//  输出: 3
//  解释: 它可以解码为 "BZ" (2 26), "VF" (22 6), 或者 "BBF" (2 2 6) 。


#include "parser.h"
#include "debug.h"
#include <queue>

int numDecodings(string s);

void TestDecodeWays()
{
    // cout << numDecodings("12");
    // cout << numDecodings("226");
    cout << numDecodings("2217");
    // cout << numDecodings("100");
    // cout << numDecodings("101");
}

// // Version: like DP, overtime
// int numDecodings(string s)
// {
//     if (s.size() == 0 || s[0] == '0')
//         return 0;

//     queue<vector<int>> resultQueue;
//     resultQueue.push(vector<int>({s[0] - '0'}));

//     for (int i = 1; i != s.size(); ++i)
//     {
//         int queueSize = resultQueue.size();
//         int currNum = s[i] - '0';

//         for (int j = 0; j != queueSize; ++j)
//         {
//             vector<int> sol = resultQueue.front();

//             if (currNum >= 1)
//             {
//                 sol.push_back(currNum);
//                 resultQueue.push(sol);
//                 sol.pop_back();
//             }

//             int lastNum = sol[sol.size() - 1] * 10 + currNum;
//             if (lastNum <= 26)
//             {
//                 sol[sol.size() - 1] = lastNum;
//                 resultQueue.push(sol);
//             }

//             resultQueue.pop();
//         }
//     }

//     return resultQueue.size();
// }

// Version, back-tracking, overtime
// void numDecodings(string &s, int index, int &count);
// int numDecodings(string s)
// {
//     if (s.size() == 0 || s[0] == '0')
//         return 0;

//     int result = 0;
//     numDecodings(s, 0, result);
//     return result;
// }

// void numDecodings(string &s, int index, int &count)
// {
//     if (index >= s.size())
//     {
//         count++;
//         return;
//     }

//     int oneNum = s[index] - '0';
//     if (oneNum >= 1)
//     {
//         numDecodings(s, index + 1, count);
//     }

//     if (index != s.size() - 1 && s[index] != '0')
//     {
//         int twoNum = (s[index] - '0') * 10 + (s[index + 1] - '0');
//         if (twoNum >= 1 && twoNum <= 26)
//             numDecodings(s, index + 2, count);
//     }
// }

int numDecodings(string s)
{
    if (s.size() == 0 || s[0] == '0')
        return 0;

    int prev = 1, curr = 1; // prev-> minus 2 digits, curr -> minus 1 digit

    for (int i = 1; i != s.size(); ++i)
    {
        int temp = curr;
        if (s[i] == '0') // must handle 2 digits
        {
            if (s[i - 1] == '1' || s[i - 1] == '2')
                curr = prev;
            else
                return 0; // sth like 40 exists in string
        }
        else
        {
            // cases of 221 = cases of 21 + cases of 2
            // cases of 227 = cases of 22

            // can handle two digits
            if (s[i - 1] == '1' || (s[i - 1] == '2' && (s[i] >= '1' && s[i] <= '6')))
                curr = curr + prev; // sum of two cases
            // else curr= curr
        }

        prev = temp;
    }

    return curr;
}
