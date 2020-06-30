// 岛屿数量

// 难度：中等

// Tags：

// breadth first searching | depth first searching

// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

// 岛屿总是被水包围，并且每座岛屿只能由水平方向或竖直方向上相邻的陆地连接形成。

// 此外，你可以假设该网格的四条边均被水包围。

// 示例 1:

// 输入:
// 11110
// 11010
// 11000
// 00000
// 输出: 1

// 示例 2:

// 输入:
// 11000
// 11000
// 00100
// 00011
// 输出: 3
// 解释: 每座岛屿只能由水平和/或竖直方向上相邻的陆地连接而成。

#include "parser.h"
#include "debug.h"
#include <unordered_map>

int numIslands(vector<vector<char>> &grid);
void TestNumIslands()
{
    // vector<vector<char>> grid = parser2VectorArray_char("11110,11010,11000,00000");
    // vector<vector<char>> grid = parser2VectorArray_char("111,010,111");
    // vector<vector<char>> grid = parser2VectorArray_char("10111,10101,11101");
    vector<vector<char>> grid = parser2VectorArray_char("11000,11000,00100,00011");
    int result = numIslands(grid);
    cout << "result is " << result << endl;
}

// Version: DFS
void touchIslands(vector<vector<char>> &grid, vector<vector<bool>> &visited, const int &rowSize, const int &colSize, int i, int j);
int numIslands(vector<vector<char>> &grid)
{
    int rowSize = grid.size();
    if (rowSize == 0)
        return 0;

    int colSize = grid[0].size();
    if (colSize == 0)
        return 0;

    int islandsNum = 0;
    vector<vector<bool>> visited = vector<vector<bool>>(rowSize, vector<bool>(colSize, false));

    for (int i = 0; i != rowSize; ++i)
    {
        for (int j = 0; j != colSize; ++j)
        {
            if (grid[i][j] == '0' || visited[i][j])
                continue;
            islandsNum++;
            touchIslands(grid, visited, rowSize, colSize, i, j);
        }
    }
    DebugVectorArray(visited);
    return islandsNum;
}

void touchIslands(vector<vector<char>> &grid, vector<vector<bool>> &visited, const int &rowSize, const int &colSize,
                  int i, int j)
{
    visited[i][j] = true;
    if (j - 1 >= 0 && grid[i][j - 1] != '0' && !visited[i][j - 1])
        touchIslands(grid, visited, rowSize, colSize, i, j - 1);
    if (j + 1 < colSize && grid[i][j + 1] != '0' && !visited[i][j + 1])
        touchIslands(grid, visited, rowSize, colSize, i, j + 1);
    if (i - 1 >= 0 && grid[i - 1][j] != '0' && !visited[i - 1][j])
        touchIslands(grid, visited, rowSize, colSize, i - 1, j);
    if (i + 1 < rowSize && grid[i + 1][j] != '0' && !visited[i + 1][j])
        touchIslands(grid, visited, rowSize, colSize, i + 1, j);
}

// Version: BFS
//TODO
