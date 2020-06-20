// Pow(x, n)

// 难度：中等

// Tags
// math | divide-and-conquer

// 实现 pow(x, n) ，即计算 x 的 n 次幂函数。

// 示例 1:

// 输入: 2.00000, 10
// 输出: 1024.00000

// 示例 2:

// 输入: 2.10000, 3
// 输出: 9.26100

// 示例 3:

// 输入: 2.00000, -2
// 输出: 0.25000
// 解释: 2-2 = 1/22 = 1/4 = 0.25

#include <iostream>
using namespace std;

double myPow(double x, int n);

void TestPow()
{
    double result = myPow(2, -2);
    cout << "result is" << result << endl;
}

// Version: Divide and Conquer

double myPow(double x, int n)
{
    if (x == 0)
        return 0.0;
    if (n == 0)
        return 1.0;
    if (n == 1)
        return x;
    if (n == -1)
        return 1.0 / x;

    double result = myPow(x, n / 2);
    int remainder = n % 2;

    return result * result * (remainder == 0 ? 1 : (remainder == 1 ? x : 1.0 / x));
}

// Version: Math
// https://leetcode-cn.com/problems/powx-n/solution/powx-n-by-leetcode-solution/