// 求1+2+…+n

// 难度：中等

// 标签：

// 数学

// 求 1+2+...+n ，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。

// 示例 1：

// 输入: n = 3
// 输出: 6

// 示例 2：

// 输入: n = 9
// 输出: 45

#include <iostream>

using namespace std;

int sumNums(int n);

void TestSumNums()
{
    int result = sumNums(10);
    cout << "result is " << result << endl;
}

int sumNums(int n)
{
    (n == 0) || (n += sumNums(n - 1));
    return n;
}