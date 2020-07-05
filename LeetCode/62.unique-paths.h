// 不同路径

// 难度：中等

// Tags
// array | dynamic-programming

// 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

// 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。

// 问总共有多少条不同的路径？

// 示例 1:

// 输入: m = 3, n = 2
// 输出: 3
// 解释:
// 从左上角开始，总共有 3 条路径可以到达右下角。
// 1. 向右 -> 向右 -> 向下
// 2. 向右 -> 向下 -> 向右
// 3. 向下 -> 向右 -> 向右

// 示例 2:

// 输入: m = 7, n = 3
// 输出: 28

#include "parser.h"
#include "debug.h"
#include <queue>

int uniquePaths(int m, int n);

void TestUniquePath()
{
    int result = uniquePaths(7, 3);
    cout << result << endl;
}

// // Version: back tracking
// void backTracking(const int rowSize, const int colSize, int i, int j, int &times);
// int uniquePaths(int m, int n)
// {
//     int times = 0;
//     backTracking(n, m, 0, 0, times);
//     return times;
// }

// void backTracking(const int rowSize, const int colSize, int i, int j, int &times)
// {
//     if (i >= rowSize || j >= colSize)
//         return;
//     if (i == rowSize - 1 && j == colSize - 1)
//     {
//         times++;
//         return;
//     }

//     backTracking(rowSize, colSize, i + 1, j, times); // down
//     backTracking(rowSize, colSize, i, j + 1, times); // right
// }

// Version: dynamic programing
int uniquePaths(int m, int n)
{
    int rowSize = n, colSize = m;

    vector<vector<int>> timesVec = vector<vector<int>>(rowSize, vector<int>(colSize, 0));
    timesVec[rowSize - 1][colSize - 1] = 1;

    for (int i = rowSize - 1; i >= 0; --i)
    {
        for (int j = colSize - 1; j >= 0; --j)
        {
            timesVec[i][j] += (i + 1 < rowSize) ? timesVec[i + 1][j] : 0;
            timesVec[i][j] += (j + 1 < colSize) ? timesVec[i][j + 1] : 0;
        }
    }

    return timesVec[0][0];
}