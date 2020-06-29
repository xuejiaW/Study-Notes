// 整数反转

// 难度：简单

// Tags：
// Math

// 给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转。

// 示例 1:

// 输入: 123
// 输出: 321
//  示例 2:

// 输入: -123
// 输出: -321
// 示例 3:

// 输入: 120
// 输出: 21
// 注意:

// 假设我们的环境只能存储得下 32 位的有符号整数，则其数值范围为 [−231,  231 − 1]。请根据这个假设，如果反转后整数溢出那么就返回 0。

#include <iostream>

using namespace std;

int reverse(int x);

void TestReverse()
{
    int result = reverse(-2147483648);
    cout << "result is " << result << endl;
}

int reverse(int x)
{
    if (x == INT_MIN)
        return 0;
    int limit = INT_MAX / 10;
    int result = 0;
    int flag = x < 0 ? -1 : 1;
    x = abs(x); // abs can not handle INT_MIN
    while (x != 0)
    {
        int curr = x % 10;
        if (result > limit || (result == limit && ((flag == 1 && curr > 7) || (flag == -1 && curr > 8))))
            return 0;
        result *= 10;
        result += curr;
        x /= 10;
    }

    return flag * result;
}
