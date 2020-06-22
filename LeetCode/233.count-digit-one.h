// 数字 1 的个数

// 难度：困难

// Tags:
// math

// 给定一个整数 n，计算所有小于等于 n 的非负整数中数字 1 出现的个数。

// 示例:

// 输入: 13
// 输出: 6 
// 解释: 数字 1 出现在以下数字中: 1, 10, 11, 12, 13 。

#include <iostream>
using namespace std;

int countDigitOne(int n);

void TestCountDigitOne()
{
    int result = countDigitOne(32104);
    cout << "result is " << result << endl; // should be 23626
}

// Version: math
// https://leetcode-cn.com/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/solution/mian-shi-ti-43-1n-zheng-shu-zhong-1-chu-xian-de-2/
int countDigitOne(int n)
{
    if (n <= 0)
        return 0;

    long long digit = 1;
    long long curr = n % 10, high = n / 10, low = 0;

    int count = 0;

    while (high != 0 || curr != 0)
    {
        if (curr == 0)
            count += high * digit;
        else if (curr == 1)
            count += high * digit + low + 1;
        else
            count += (high + 1) * digit;

        low += curr * digit;
        curr = high % 10;
        high /= 10;
        digit *= 10;
    }
    return count;
}
