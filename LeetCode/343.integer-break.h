// Tags:
// dynamic-programming | greedy-algorithm

// 给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积。

// 示例 1:

// 输入: 2
// 输出: 1
// 解释: 2 = 1 + 1, 1 × 1 = 1。
// 示例 2:

// 输入: 10
// 输出: 36
// 解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。
// 说明: 你可以假设 n 不小于 2 且不大于 58。

#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

int integerBreak(int n);

void TestIntegerBreak()
{
    int result = integerBreak(10);
    cout << "result is " << result << endl;
}

// // Version: Dynamic programming
// int integerBreak(int n)
// {
//     unordered_map<int, int> length2CuttedMaxMap;
//     length2CuttedMaxMap.insert({1, 1});

//     for (int i = 2; i <= n; i++)
//     {
//         for (int j = 1; j <= i / 2; j++)
//         {
//             // j -> first cutted part length
//             // (i-j) -> if second part is not cutted
//             // length2CuttedMaxMap[i - j] -> if second part is cutted
//             length2CuttedMaxMap[i] = max(length2CuttedMaxMap[i], j * max(i - j, length2CuttedMaxMap[i - j]));
//         }
//     }

//     return length2CuttedMaxMap[n];
// }

// Version: Greedy algorithm
// The max solution is trying to get more 3
int integerBreak(int n)
{
    if (n == 2)
        return 1;
    if (n == 3)
        return 2;

    int result = 1;
    while (n > 4)
    {
        result *= 3;
        n -= 3;
    }

    return result * n; // times remaining part
}
