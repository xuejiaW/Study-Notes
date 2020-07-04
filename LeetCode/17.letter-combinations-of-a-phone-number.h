// 电话号码的字母组合

// Tags
// string | backtracking

// 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。

// 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

// 示例:

// 输入："23"
// 输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
// 说明:
// 尽管上面的答案是按字典序排列的，但是你可以任意选择答案输出的顺序。

#include "parser.h"
#include "debug.h"
#include <unordered_map>

vector<string> letterCombinations(string digits);
void TestLetterCombinations()
{
    vector<string> result = letterCombinations("2");
    DebugVector(result);
}


void backTracking(vector<string> &result, unordered_map<char, vector<char>> &nums2Letter,
                  string &sol, const string &digits, int index, const int &maxSize);
vector<string> letterCombinations(string digits)
{
    int size = digits.size();

    vector<string> result;
    if (size == 0)
        return result;

    unordered_map<char, vector<char>> num2Letter{
        {'2', vector<char>{'a', 'b', 'c'}},
        {'3', vector<char>{'d', 'e', 'f'}},
        {'4', vector<char>{'g', 'h', 'i'}},
        {'5', vector<char>{'j', 'k', 'l'}},
        {'6', vector<char>{'m', 'n', 'o'}},
        {'7', vector<char>{'p', 'q', 'r', 's'}},
        {'8', vector<char>{'t', 'u', 'v'}},
        {'9', vector<char>{'w', 'x', 'y', 'z'}}};

    string sol;
    backTracking(result, num2Letter, sol, digits, 0, size);

    return result;
}

void backTracking(vector<string> &result, unordered_map<char, vector<char>> &nums2Letter,
                  string &sol, const string &digits, int index, const int &maxSize)
{
    if (index >= maxSize)
    {
        result.push_back(sol);
        return;
    }

    const vector<char> &letters = nums2Letter[digits[index]];
    for (int i = 0; i != letters.size(); ++i)
    {
        sol.push_back(letters[i]);
        backTracking(result, nums2Letter, sol, digits, index + 1, maxSize);
        sol.pop_back();
    }
}
