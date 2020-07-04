// 岛屿的最大面积

// 难度：
// 中等

// Tags
// array | depth-first-search

// 给定一个包含了一些 0 和 1 的非空二维数组 grid 。

// 一个 岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在水平或者竖直方向上相邻。你可以假设 grid 的四个边缘都被 0（代表水）包围着。

// 找到给定的二维数组中最大的岛屿面积。(如果没有岛屿，则返回面积为 0 。)

// 示例 1:

// [[0,0,1,0,0,0,0,1,0,0,0,0,0],
//  [0,0,0,0,0,0,0,1,1,1,0,0,0],
//  [0,1,1,0,1,0,0,0,0,0,0,0,0],
//  [0,1,0,0,1,1,0,0,1,0,1,0,0],
//  [0,1,0,0,1,1,0,0,1,1,1,0,0],
//  [0,0,0,0,0,0,0,0,0,0,1,0,0],
//  [0,0,0,0,0,0,0,1,1,1,0,0,0],
//  [0,0,0,0,0,0,0,1,1,0,0,0,0]]
// 对于上面这个给定矩阵应返回 6。注意答案不应该是 11 ，因为岛屿只能包含水平或垂直的四个方向的 1 。

// 示例 2:

// [[0,0,0,0,0,0,0,0]]
// 对于上面这个给定的矩阵, 返回 0。

#include "parser.h"
#include "debug.h"
#include <algorithm>

int maxAreaOfIsland(vector<vector<int>> &grid);
void TestMaxAreaOfIsland()
{
    vector<vector<int>> grid = parser2VectorArray_int("[[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]");
    int result = maxAreaOfIsland(grid);
    cout << result << endl;
}

// Version: dfs
int touchIsland(vector<vector<bool>> &visited, vector<vector<int>> &gird, int i, int j, const int &rowSize, const int &colSize);
int maxAreaOfIsland(vector<vector<int>> &grid)
{
    if (grid.empty() || grid[0].empty())
        return 0;

    int rowSize = grid.size(), colSize = grid[0].size();
    int maxArea = 0;
    vector<vector<bool>> visited(rowSize, vector<bool>(colSize, false));
    for (int i = 0; i != rowSize; ++i)
    {
        for (int j = 0; j != colSize; ++j)
        {
            if (visited[i][j] || !grid[i][j])
                continue;
            maxArea = max(maxArea, touchIsland(visited, grid, i, j, rowSize, colSize));
        }
    }
    return maxArea;
}

int touchIsland(vector<vector<bool>> &visited, vector<vector<int>> &gird, int i, int j, const int &rowSize, const int &colSize)
{
    if (i < 0 || i >= rowSize || j < 0 || j >= colSize || visited[i][j] || !gird[i][j])
        return 0;

    visited[i][j] = true;
    int result = touchIsland(visited, gird, i + 1, j, rowSize, colSize) +
                 touchIsland(visited, gird, i - 1, j, rowSize, colSize) +
                 touchIsland(visited, gird, i, j + 1, rowSize, colSize) +
                 touchIsland(visited, gird, i, j - 1, rowSize, colSize) + 1;
    return result;
}
