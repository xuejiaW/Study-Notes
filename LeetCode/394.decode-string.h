// 字符串解码

// 难度：中等

// Tags
// stack | depth-first-search

// 给定一个经过编码的字符串，返回它解码后的字符串。

// 编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

// 你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

// 此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

// 示例 1：
// 输入：s = "3[a]2[bc]"
// 输出："aaabcbc"

// 示例 2：
// 输入：s = "3[a2[c]]"
// 输出："accaccacc"

// 示例 3：
// 输入：s = "2[abc]3[cd]ef"
// 输出："abcabccdcdcdef"

// 示例 4：
// 输入：s = "abc3[cd]xyz"
// 输出："abccdcdcdxyz"

#include "debug.h"
#include "parser.h"
#include <stack>

string decodeString(string s);
void TestDecodeString()
{
    // cout << decodeString("3[a]2[bc]") << endl;
    // cout << decodeString("3[a2[c]]")<<endl;
    // cout << decodeString("2[abc]3[cd]ef")<<endl;
    // cout << decodeString("100[leetcode]") << endl;
    cout << decodeString("2[2[y]pq4[2[jk]e1[f]]]ef") << endl;
}

// // Version: stack
// string decodeString(string s)
// {
//     string result = "";

//     stack<string> duplicateTargetsStack;
//     stack<int> duplicateTimeStack;
//     int currNum = 0;

//     for (const char &c : s)
//     {
//         if (c == '[')
//         {
//             duplicateTimeStack.push(currNum);
//             duplicateTargetsStack.push("");
//             currNum = 0;
//         }
//         else if (isdigit(c))
//         {
//             currNum *= 10;
//             currNum += (c - '0');
//         }
//         else if (isalpha(c))
//         {
//             if (!duplicateTargetsStack.empty())
//             {
//                 string &target = duplicateTargetsStack.top();
//                 target.push_back(c);
//             }
//             else
//                 result.push_back(c);
//         }
//         else if (c == ']')
//         {
//             string target = duplicateTargetsStack.top();
//             duplicateTargetsStack.pop();
//             int times = duplicateTimeStack.top();
//             duplicateTimeStack.pop();

//             for (int i = 0; i != times; ++i)
//             {
//                 if (duplicateTargetsStack.empty())
//                     result += target;
//                 else
//                     duplicateTargetsStack.top() += target;
//             }
//         }
//     }

//     return result;
// }

// Version: recurrance
// TODO