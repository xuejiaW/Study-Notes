// 有效的括号

// 难度：简单

// Tags
// string | stack


// 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。

// 有效字符串需满足：

// 左括号必须用相同类型的右括号闭合。
// 左括号必须以正确的顺序闭合。
// 注意空字符串可被认为是有效字符串。

// 示例 1:

// 输入: "()"
// 输出: true
// 示例 2:

// 输入: "()[]{}"
// 输出: true
// 示例 3:

// 输入: "(]"
// 输出: false
// 示例 4:

// 输入: "([)]"
// 输出: false
// 示例 5:

// 输入: "{[]}"
// 输出: true

#include <string>
#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;

bool isValid(string s);
void TestIsValid()
{
    bool result = isValid("{[)}");
    // bool result = isValid("()[]{}");
    cout << "result is " << result << endl;
}

bool isValid(string s)
{
    if (s.empty())
        return true;

    unordered_map<char, int> leftParanthese;
    leftParanthese.insert({'(', 0});
    leftParanthese.insert({'[', 1});
    leftParanthese.insert({'{', 2});

    unordered_map<char, int> rightParenthese;
    rightParenthese.insert({')', 0});
    rightParenthese.insert({']', 1});
    rightParenthese.insert({'}', 2});

    stack<char> auxiliary;

    for (int i = 0; i != s.size(); ++i)
    {
        if (leftParanthese.find(s[i]) != leftParanthese.end())
            auxiliary.push(s[i]);
        if (rightParenthese.find(s[i]) != rightParenthese.end())
        {
            if (auxiliary.empty() || leftParanthese[auxiliary.top()] != rightParenthese[s[i]])
                return false;
            else
                auxiliary.pop();
        }
    }

    return auxiliary.empty();
}
