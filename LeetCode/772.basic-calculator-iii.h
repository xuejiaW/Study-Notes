#include "parser.h"
#include "debug.h"
#include <stack>

int calculate(string s);
void TestCalculate()
{
    cout << calculate("2 + 3 * 5 + 2") << endl;
    cout << calculate("1+(2+3)+1") << endl;
    cout << calculate("3 * (2 * 3)") << endl;
    cout << calculate("2*(5+5*2)/3+(6/2+8)") << endl;
    cout << calculate("(2+6* 3+5- (3*14/7+2)*5)+3") << endl;
}

int calculate(string s)
{
    stack<long> numStack;
    stack<char> prevOperationStack;
    char prevOperation = '+';
    long result = 0, prevPart = 0, currPart = 0;
    long sSize = s.size();

    for (int i = 0; i != sSize; ++i)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            currPart *= 10;
            currPart += s[i] - '0';
        }

        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || i == sSize - 1 || s[i] == ')')
        {
            if (prevOperation == '+') // prevPart must be zero
                prevPart += currPart;
            else if (prevOperation == '-') // pervPart must be zero
                prevPart -= currPart;
            else if (prevOperation == '*')
                prevPart *= currPart;
            else if (prevOperation == '/')
                prevPart /= currPart;

            if (s[i] == '+' || s[i] == '-' || i == sSize - 1 || s[i] == ')')
            {
                result += prevPart;
                prevPart = 0;
            }

            prevOperation = s[i] == ')' ? '+' : s[i];
            currPart = 0;
        }

        if (s[i] == '(')
        {
            numStack.push(prevPart);
            numStack.push(result);
            prevOperationStack.push(prevOperation);

            prevOperation = '+';
            prevPart = 0;
            currPart = 0;
            result = 0;
        }

        if (s[i] == ')')
        {
            prevOperation = prevOperationStack.top();
            prevOperationStack.pop();

            currPart = result;
            result = numStack.top();
            numStack.pop();

            prevPart = numStack.top();
            numStack.pop();

            if (prevOperation == '+')
                prevPart += currPart;
            else if (prevOperation == '-')
                prevPart -= currPart;
            else if (prevOperation == '*')
                prevPart *= currPart;
            else if (prevOperation == '/')
                prevPart /= currPart;

            if (i == (sSize - 1))
            {
                result += prevPart;
                prevPart = 0;
            }
            else
            {
                currPart = 0;
                prevOperation = '+';
            }
        }
    }

    return result;
}