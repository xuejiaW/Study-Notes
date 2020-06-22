// 礼物的最大价值

// 难度：中等

// Tags:
// Dynamic programming

// 在一个 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于 0）。你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格、直到到达棋盘的右下角。给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？

//  

// 示例 1:

// 输入: 
// [
//   [1,3,1],
//   [1,5,1],
//   [4,2,1]
// ]
// 输出: 12
// 解释: 路径 1→3→5→2→1 可以拿到最多价值的礼物

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxValue(vector<vector<int>> &grid);

void testMaxValue()
{
    vector<vector<int>> grid = {
        {1, 3, 1},
        {1, 5, 1},
        {4, 2, 1}};

    int result = maxValue(grid);
    cout << "result max is " << result << endl;
}

int maxValue(vector<vector<int>> &grid)
{
    if (grid.empty() || grid[0].empty())
        return 0;

    int rowSize = grid.size(), colSize = grid[0].size();

    vector<vector<int>> maxValueGrid;
    for (int i = 0; i != rowSize; ++i)
        maxValueGrid.push_back(vector<int>(colSize));

    for (int i = 0; i != rowSize; ++i)
    {
        for (int j = 0; j != colSize; ++j)
        {
            if (i == 0 && j == 0)
                maxValueGrid[i][j] = grid[0][0];
            else if (i == 0)
                maxValueGrid[i][j] = maxValueGrid[0][j - 1] + grid[0][j];
            else if (j == 0)
                maxValueGrid[i][j] = maxValueGrid[i - 1][0] + grid[i][0];
            else
                maxValueGrid[i][j] = max(maxValueGrid[i - 1][j] + grid[i][j], maxValueGrid[i][j - 1] + grid[i][j]);
        }
    }

    return maxValueGrid[rowSize - 1][colSize - 1];
}