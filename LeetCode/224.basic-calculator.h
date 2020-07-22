// 基本计算器

// 难度：困难

// Tags:
// Stack

// 实现一个基本的计算器来计算一个简单的字符串表达式的值。

// 字符串表达式可以包含左括号 ( ，右括号 )，加号 + ，减号 -，非负整数和空格  。

// 示例 1:

// 输入: "1 + 1"
// 输出: 2
// 示例 2:

// 输入: " 2-1 + 2 "
// 输出: 3
// 示例 3:

// 输入: "(1+(4+5+2)-3)+(6+8)"
// 输出: 23

#include "parser.h"
#include "debug.h"
#include <stack>

int calculate(string s);
void TestCalculate()
{
    int result = calculate("(1+(4+5+2)-3)+(6+8)");
    // int result = calculate("1-(3-4)");
    // int result = calculate("1+3+4-(2-3)");
    cout << result << endl;
}

int calculate(string s)
{
    stack<int> resultStack;
    int sSize = s.size();
    int result = 0, flag = 1, curr = 0;
    for (int i = 0; i != sSize; ++i)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            curr *= 10;
            curr += (s[i] - '0');
        }

        if (s[i] == '+' || s[i] == '-' || s[i] == ')' || i == sSize - 1)
        {
            result += flag * curr;
            flag = s[i] == '+' ? 1 : -1;
            curr = 0;
        }

        if (s[i] == '(')
        {
            resultStack.push(result);
            resultStack.push(flag);
            result = 0;
            curr = 0;
            flag = 1;
        }

        if (s[i] == ')')
        {
            // result represents the result in the bracket
            result *= resultStack.top();
            resultStack.pop();
            // the result within the bracket + result without the bracket(restore in the stack)
            result += resultStack.top();
            resultStack.pop();
            curr = 0;
        }
    }
    return result;
}
