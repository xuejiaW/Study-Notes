// 最小路径和

// 难度：中等

// Tags:

// array| dynamic-programming

// 给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

// 说明：每次只能向下或者向右移动一步。

// 示例:

// 输入:
// [
//   [1,3,1],
//   [1,5,1],
//   [4,2,1]
// ]
// 输出: 7
// 解释: 因为路径 1→3→1→1→1 的总和最小。

#include "parser.h"
#include "debug.h"

int minPathSum(vector<vector<int>> &grid);
void TestMinPathSum()
{
    vector<vector<int>> gird{
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1},
    };
    int result = minPathSum(gird);
    cout << result << endl;
}

// Version: dynamic programming
int minPathSum(vector<vector<int>> &grid)
{
    int rowSize = grid.size(), colSize = rowSize == 0 ? 0 : grid[0].size();
    if (rowSize == 0 || colSize == 0)
        return 0;

    vector<vector<int>> minPathVec = vector<vector<int>>(rowSize, vector<int>(colSize, 0));

    for (int i = rowSize - 1; i >= 0; --i)
    {
        for (int j = colSize - 1; j >= 0; --j)
        {
            int down = i + 1 < rowSize ? minPathVec[i + 1][j] : INT_MAX;
            int right = j + 1 < colSize ? minPathVec[i][j + 1] : INT_MAX;
            int minVal = min(down, right);
            minPathVec[i][j] = grid[i][j] + (minVal != INT_MAX ? minVal : 0);
        }
    }
    return minPathVec[0][0];
}
