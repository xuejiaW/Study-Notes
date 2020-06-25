// 爬楼梯

// 难度：简单

// Tags: 
// dynamic-programming

// 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

// 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

// 注意：给定 n 是一个正整数。

// 示例 1：

// 输入： 2
// 输出： 2
// 解释： 有两种方法可以爬到楼顶。
// 1.  1 阶 + 1 阶
// 2.  2 阶
// 示例 2：

// 输入： 3
// 输出： 3
// 解释： 有三种方法可以爬到楼顶。
// 1.  1 阶 + 1 阶 + 1 阶
// 2.  1 阶 + 2 阶
// 3.  2 阶 + 1 阶

#include <vector>
#include <iostream>

using namespace std;

int climbStairs(int n);

void TestClimbStairs()
{
    int result = climbStairs(1);
    cout << "result is " << result << endl;
}

int climbStairs(int n)
{
    if (n == 1)
        return 1;
    vector<int> solutionVec(n);
    solutionVec[0] = 1; // one step
    solutionVec[1] = 2; // two step
    for (int i = 2; i != n; ++i)
    {
        solutionVec[i] = solutionVec[i - 1] + solutionVec[i - 2];
    }
    return solutionVec[n - 1];
}
