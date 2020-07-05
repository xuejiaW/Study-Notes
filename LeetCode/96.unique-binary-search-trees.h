// 不同的二叉搜索树

// 难度：中等

// Tags:
// dynamic-programming | tree

// 给定一个整数 n，求以 1 ... n 为节点组成的二叉搜索树有多少种？

// 输入: 3
// 输出: 5
// 解释:
// 给定 n = 3, 一共有 5 种不同结构的二叉搜索树:

//    1         3     3      2      1
//     \       /     /      / \      \
//      3     2     1      1   3      2
//     /     /       \                 \
//    2     1         2                 3

#include "debug.h"

int numTrees(int n);
void TestNumTrees()
{
    int result = numTrees(5);
    cout << result << endl;
}

// Version: dynamic programming
int numTrees(int n)
{
    if (n <= 1)
        return 1;
    vector<int> numsVec(n + 1);
    numsVec[0] = 1;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            numsVec[i] += numsVec[j - 1] * numsVec[i - j];

    return numsVec[n];
}
