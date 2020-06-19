// 位1的个数

// Tags:
// bit-manipulation

// 编写一个函数，输入是一个无符号整数，返回其二进制表达式中数字位数为 ‘1’ 的个数（也被称为汉明重量）。

// 示例 1：

// 输入：00000000000000000000000000001011
// 输出：3
// 解释：输入的二进制串 00000000000000000000000000001011 中，共有三位为 '1'。
// 示例 2：

// 输入：00000000000000000000000010000000
// 输出：1
// 解释：输入的二进制串 00000000000000000000000010000000 中，共有一位为 '1'。
// 示例 3：

// 输入：11111111111111111111111111111101
// 输出：31
// 解释：输入的二进制串 11111111111111111111111111111101 中，共有 31 位为 '1'。

#include <iostream>

using namespace std;

int hammingWeight(uint32_t n);

void TestHammingWeight()
{
    int result = hammingWeight(8);
    // unsigned int a = 1 << 31;
    // uint32_t b = 4;
    // cout << (b & a) << endl;
    cout << "result is" << result << endl;
}

// // Version: using 1 << 31
// int hammingWeight(uint32_t n)
// {
//     unsigned int target = 1 << 31;
//     int result = 0;
//     while (target != 0)
//     {
//         result += (n & target) ? 1 : 0;
//         target >>= 1;
//     }
//     return result;
// }

// Version: using  n & (n-1)
int hammingWeight(uint32_t n)
{
    int result = 0;
    while (n)
    {
        n &= (n - 1);
        result++;
    }
    return result;
}
