// 最大正方形

// 难度：中等

// Tags:

// dynamic-programmming

// 在一个由 0 和 1 组成的二维矩阵内，找到只包含 1 的最大正方形，并返回其面积。

// 示例:

// 输入:

// 1 0 1 0 0
// 1 0 1 1 1
// 1 1 1 1 1
// 1 0 0 1 0

// 输出: 4

#include "parser.h"
#include "debug.h"
#include <algorithm>

int maximalSquare(vector<vector<char>> &matrix);

void TestMaxSquare()
{
    vector<vector<char>> matrix = parser2VectorArray_char("10100,10111,11111,10010");
    int result = maximalSquare(matrix);
    cout << result << endl;
}

// Version: dynamic programming
int maximalSquare(vector<vector<char>> &matrix)
{
    int rowSize = matrix.size(), colSize = rowSize == 0 ? 0 : matrix[0].size();
    if (rowSize == 0 || colSize == 0)
        return 0;

    vector<vector<int>> squareSizeVec(rowSize, vector<int>(colSize, 0));
    int maxSize = 0;

    for (int i = 0; i != rowSize; ++i)
    {
        for (int j = 0; j != colSize; ++j)
        {
            if (matrix[i][j] == '0') // only calculating 1 elements
                continue;

            if (i == 0 || j == 0 || !squareSizeVec[i - 1][j - 1])
            {
                maxSize = max(maxSize, 1);
                squareSizeVec[i][j] = 1;
            }
            else
            {
                int surround = min(squareSizeVec[i - 1][j - 1], min(squareSizeVec[i - 1][j], squareSizeVec[i][j - 1]));
                squareSizeVec[i][j] = surround + 1;
                maxSize = max(maxSize, surround + 1);
            }
        }
    }

    return maxSize * maxSize;
}
