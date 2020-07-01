// 括号生成

// 难度：中等

// Tags:

// string| back tracking

// 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

// 示例：

// 输入：n = 3
// 输出：[
//        "((()))",
//        "(()())",
//        "(())()",
//        "()(())",
//        "()()()"
//      ]

#include "parser.h"
#include "debug.h"

vector<string> generateParenthesis(int n);

void TestGenerateParenthesis()
{
    vector<string> result = generateParenthesis(4);
    DebugVector(result);
}

// Version: back tracking
void backTracking(vector<string> &result, string &sol, int leftRemain, int rightRemain, const int &num);
vector<string> generateParenthesis(int n)
{
    vector<string> result;
    string sol = "";
    backTracking(result, sol, n, 0, n);
    return result;
}

void backTracking(vector<string> &result, string &sol, int leftRemain, int rightRemain, const int &num)
{
    if (sol.size() == 2 * num)
    {
        result.push_back(sol);
        return;
    }

    if (leftRemain > 0)
    {
        sol.push_back('(');
        backTracking(result, sol, leftRemain - 1, rightRemain + 1, num);
        sol.pop_back();
    }
    if (rightRemain > 0)
    {
        sol.push_back(')');
        backTracking(result, sol, leftRemain, rightRemain - 1, num);
        sol.pop_back();
    }
}
