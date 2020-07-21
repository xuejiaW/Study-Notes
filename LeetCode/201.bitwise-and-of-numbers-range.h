// 数字范围按位与

// 难度：中等

// Tags
// bit-manipulation

// 给定范围 [m, n]，其中 0 <= m <= n <= 2147483647，返回此范围内所有数字的按位与（包含 m, n 两端点）。

// 示例 1: 

// 输入: [5,7]
// 输出: 4

// 示例 2:

// 输入: [0,1]
// 输出: 0

#include "parser.h"
#include "debug.h"

int rangeBitwiseAnd(int m, int n);

void TestRangeBitWiseAnd()
{
    int result = rangeBitwiseAnd(5, 7);
    cout << result << endl;
}

int rangeBitwiseAnd(int m, int n)
{
    int moveCount = 0;
    while (m != n)
    {
        m >>= 1;
        n >>= 1;
        moveCount++;
    }
    n <<= moveCount;
    return n;
}
