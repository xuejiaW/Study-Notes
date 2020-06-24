// 圆圈中最后剩下的数字

// 难度：简单

// 标签：

// 数学

// 0,1,,n-1这n个数字排成一个圆圈，从数字0开始，每次从这个圆圈里删除第m个数字。求出这个圆圈里剩下的最后一个数字。

// 例如，0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。

// 示例 1：
// 输入: n = 5, m = 3
// 输出: 3

// 示例 2：
// 输入: n = 10, m = 17
// 输出: 2

#include <iostream>
using namespace std;

int lastRemaining(int n, int m);

void testLastRemaining()
{
    int result = lastRemaining(10, 17);
    cout << "result is " << result << endl;
}

// Explanation:
// https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/solution/huan-ge-jiao-du-ju-li-jie-jue-yue-se-fu-huan-by-as/
// f(n,m) = [ f(n-1,m) + m ] % n;

// // Version: recurrance, from top to bottom
// int lastRemaining(int n, int m)
// {
//     if (n == 1)
//         return 0;
//     return (m + lastRemaining(n - 1, m)) % n;
// }

// Version: iterative, from bottom to top
int lastRemaining(int n, int m)
{
    if (n == 1)
        return 0;

    int result = 0;
    for (int i = 2; i <= n; ++i)
        result = (result + m) % i;

    return result;
}
