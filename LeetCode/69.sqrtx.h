// x 的平方根

// 难度：
// 简单

// Tags
// math | binary-search

// 实现 int sqrt(int x) 函数。

// 计算并返回 x 的平方根，其中 x 是非负整数。

// 由于返回类型是整数，结果只保留整数的部分，小数部分将被舍去。

// 示例 1:
// 输入: 4
// 输出: 2

// 示例 2:
// 输入: 8
// 输出: 2
// 说明: 8 的平方根是 2.82842..., 
//      由于返回类型是整数，小数部分将被舍去。

#include <iostream>

using namespace std;

int mySqrt(int x);

void TestMySqrt()
{
    int result = mySqrt(1);
    cout << result << endl;
}

// // Version: violent
// int mySqrt(int x)
// {
//     for (long long i = 0; i <= x; ++i) // using long long to avoid over range
//     {
//         if (i * i == x || ((i + 1) * (i + 1) > x))
//             return i;
//     }
//     return -1;
// }

// Version: binary search
int mySqrt(int x)
{
    int left = 0, right = x, res = 0;
    while (left <= right)
    {
        int middle = (left + right) / 2;

        if ((long long)middle * middle <= x)
        {
            res = middle;
            left = middle + 1;
        }
        else
            right = middle - 1;
    }
    return res;
}

// Version: math->newtown method