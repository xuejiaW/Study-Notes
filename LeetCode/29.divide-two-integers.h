// 两数相除：

// 难度：中等

// Tags：

// math | design | binary-search

// 给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。

// 返回被除数 dividend 除以除数 divisor 得到的商。

// 整数除法的结果应当截去（truncate）其小数部分，例如：truncate(8.345) = 8 以及 truncate(-2.7335) = -2

// 示例 1:
// 输入: dividend = 10, divisor = 3
// 输出: 3
// 解释: 10/3 = truncate(3.33333..) = truncate(3) = 3

// 示例 2:
// 输入: dividend = 7, divisor = -3
// 输出: -2
// 解释: 7/-3 = truncate(-2.33333..) = -2

// 提示：

// 被除数和除数均为 32 位有符号整数。
// 除数不为 0。
// 假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−231,  231 − 1]。本题中，如果除法结果溢出，则返回 231 − 1。

#include <iostream>

int divide(int dividend, int divisor);

void TestDivideTwoIntegers()
{
    std::cout << divide(2147483647, 2) << std::endl;
}

long long div_Helper(long long dividend, long long divisor)
{
    if (dividend < divisor)
        return 0;

    long long result = 1, currSum = divisor;

    while ((currSum + currSum) < dividend)
    {
        result += result;
        currSum += currSum;
    }

    return result + div_Helper(dividend - currSum, divisor);
}

int divide(int dividend, int divisor)
{
    if (dividend == 0)
        return 0;
    if (divisor == 1)
        return dividend;
    if (divisor == -1)
        return dividend == INT_MIN ? INT_MAX : -dividend;

    int dividendFlag = dividend >= 0 ? 1 : -1, divisorFlag = divisor >= 0 ? 1 : -1;

    dividend = abs(dividend), divisor = abs(divisor); // only handle the positive number

    long long result = div_Helper(dividend, divisor);
    result = (dividendFlag == divisorFlag) ? result : -result;

    if (result > INT_MAX)
        return INT_MAX;
    if (result < INT_MIN)
        return INT_MIN;
    return result;
}
