// 通配符匹配

// 难度：困难

// Tags
// string | dynamic-programming | backtracking | greedy

// 给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。

// '?' 可以匹配任何单个字符。
// '*' 可以匹配任意字符串（包括空字符串）。
// 两个字符串完全匹配才算匹配成功。

// 说明:

// s 可能为空，且只包含从 a-z 的小写字母。
// p 可能为空，且只包含从 a-z 的小写字母，以及字符 ? 和 *。

// 示例 1:
// 输入:
// s = "aa"
// p = "a"
// 输出: false
// 解释: "a" 无法匹配 "aa" 整个字符串。

// 示例 2:
// 输入:
// s = "aa"
// p = "*"
// 输出: true
// 解释: '*' 可以匹配任意字符串。

// 示例 3:
// 输入:
// s = "cb"
// p = "?a"
// 输出: false
// 解释: '?' 可以匹配 'c', 但第二个 'a' 无法匹配 'b'。

// 示例 4:
// 输入:
// s = "adceb"
// p = "*a*b"
// 输出: true
// 解释: 第一个 '*' 可以匹配空字符串, 第二个 '*' 可以匹配字符串 "dce".

// 示例 5:
// 输入:
// s = "acdcb"
// p = "a*c?b"
// 输出: false

#include "parser.h"
#include "debug.h"

bool isMatch(string s, string p);

void TestIsMatch()
{
    // cout << isMatch("aa", "a") << endl;
    // cout << isMatch("aa", "*") << endl;
    // cout << isMatch("cb", "?a") << endl;
    // cout << isMatch("adceb", "*a*b") << endl;
    // cout << isMatch("acdcb", "a*c?b") << endl;
    cout << isMatch("mississippi", "m??*ss*?i*pi") << endl;
}

// Version: dynamic programming
bool isMatch(string s, string p)
{
    if (p == "*")
        return true;
    int sSize = s.size(), pSize = p.size();

    vector<vector<int>> dpArr(sSize + 1, vector<int>(pSize + 1, false));
    dpArr[0][0] = 1;

    for (int i = 0; i <= sSize; ++i)
    {
        for (int j = 1; j <= pSize; ++j)
        {
            if (p[j - 1] == '?')
                dpArr[i][j] = i == 0 ? 0 : dpArr[i - 1][j - 1];
            else if (p[j - 1] == '*')
            {
                dpArr[i][j] = dpArr[i][j - 1] | (i > 0 && dpArr[i - 1][j]);
            }
            else
                dpArr[i][j] = i == 0 ? false : (s[i - 1] == p[j - 1] && dpArr[i - 1][j - 1]);
        }
    }
    DebugVectorArray((dpArr));
    return dpArr[sSize][pSize];
}

// Version: greedy
