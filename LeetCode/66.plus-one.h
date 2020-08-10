// 加一

// 难度：简单

// Tags
// array

// 给定一个由整数组成的非空数组所表示的非负整数，在该数的基础上加一。

// 最高位数字存放在数组的首位， 数组中每个元素只存储单个数字。

// 你可以假设除了整数 0 之外，这个整数不会以零开头。

// 示例 1:

// 输入: [1,2,3]
// 输出: [1,2,4]
// 解释: 输入数组表示数字 123。
// 示例 2:

// 输入: [4,3,2,1]
// 输出: [4,3,2,2]
// 解释: 输入数组表示数字 4321。

#include "parser.h"
#include "debug.h"

vector<int> plusOne(vector<int> &digits);

void TestPlusOne()
{
    // vector<int> digits{1, 2, 3};
    vector<int> digits{9, 9};
    DebugVector(plusOne(digits));
}

vector<int> plusOne(vector<int> &digits)
{
    vector<int> result(digits.begin(), digits.end());
    int resultSize = result.size();
    if (resultSize == 0)
        return result;

    int i = resultSize - 1, over = 0;
    while (i >= 0)
    {
        result[i] += 1;
        over = result[i] / 10;
        if (over)
            result[i--] = 0;
        else
            break;
    }

    if (over)
        result.insert(result.begin(), 1);

    return result;
}
