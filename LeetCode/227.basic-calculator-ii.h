#include "parser.h"
#include "debug.h"
#include <stack>

int calculate(string s);
void TestCalculate()
{
    cout << calculate("3+2*2*2+4");
}

int calculate(string s)
{
    int sSize = s.size();
    int result = 0, prevPart = 0, currPart = 0;
    char prevOperation = '+';
    for (int i = 0; i != sSize; ++i)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            currPart *= 10;
            currPart += s[i] - '0';
        }

        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || i == sSize - 1)
        {
            if (prevOperation == '+') // prevPart must be zero
                prevPart += currPart;
            else if (prevOperation == '-') // prevPart must be zero
                prevPart -= currPart;
            else if (prevOperation == '*')
                prevPart *= currPart;
            else if (prevOperation == '/')
                prevPart /= currPart;

            if (s[i] == '+' || s[i] == '-' || i == sSize - 1)
            {
                result += prevPart;
                prevPart = 0;
            }

            prevOperation = s[i];
            currPart = 0;
        }
    }

    return result;
}
