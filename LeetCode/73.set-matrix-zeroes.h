// 矩阵置零

// 难度：中等

// Tags
// array

// 给定一个 m x n 的矩阵，如果一个元素为 0，则将其所在行和列的所有元素都设为 0。请使用原地算法。

// 示例 1:

// 输入: 
// [
//   [1,1,1],
//   [1,0,1],
//   [1,1,1]
// ]
// 输出: 
// [
//   [1,0,1],
//   [0,0,0],
//   [1,0,1]
// ]
// 示例 2:

// 输入: 
// [
//   [0,1,2,0],
//   [3,4,5,2],
//   [1,3,1,5]
// ]
// 输出: 
// [
//   [0,0,0,0],
//   [0,4,5,0],
//   [0,3,1,0]
// ]

#include "parser.h"
#include "debug.h"
#include <unordered_set>

void setZeroes(vector<vector<int>> &matrix);
void TestSetZeroes()
{
    // vector<vector<int>> matrix = parser2VectorArray_int("[[0,1,2,0],[3,4,5,2],[1,3,1,5]]");
    vector<vector<int>> matrix = parser2VectorArray_int("[[1,1,1],[1,0,1],[1,1,1]]");
    setZeroes(matrix);
    DebugVectorArray(matrix);
}

// // Version: with outer space
// void setZeroes(vector<vector<int>> &matrix)
// {
//     unordered_set<int> toDeleteRow;
//     unordered_set<int> toDeleteCol;
//     int rowSize = matrix.size();
//     int colSize = rowSize >= 1 ? matrix[0].size() : 0;

//     for (int i = 0; i != rowSize; ++i)
//     {
//         for (int j = 0; j != colSize; ++j)
//         {
//             if (matrix[i][j] == 0)
//             {
//                 toDeleteRow.insert(i);
//                 toDeleteCol.insert(j);
//             }
//         }
//     }

//     for (unordered_set<int>::iterator i = toDeleteRow.begin(); i!= toDeleteRow.end(); ++i)
//     {
//         for (int j = 0; j != colSize; ++j)
//         {
//             matrix[*i][j] = 0;
//         }
//     }

//     for (unordered_set<int>::iterator j = toDeleteCol.begin(); j!= toDeleteCol.end(); ++j)
//     {
//         for (int i = 0; i != rowSize; ++i)
//         {
//             matrix[i][*j] = 0;
//         }
//     }
// }

// Version: no outer space
void setZeroes(vector<vector<int>> &matrix)
{
    int rowsize = matrix.size();
    int colsize = rowsize >= 1 ? matrix[0].size() : 0;
    bool needhandlefirstRow = false;
    bool needhandlefirstCol = false;

    for (int i = 0; i != rowsize; ++i)
    {
        for (int j = 0; j != colsize; ++j)
        {
            if (matrix[i][j] == 0)
            {
                if (i == 0)
                    needhandlefirstRow = true;
                if (j == 0)
                    needhandlefirstCol = true;
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }

    for (int i = 1; i != rowsize; ++i)
    {
        for (int j = 1; j != colsize; ++j)
        {
            if (matrix[i][0] == 0 || matrix[0][j] == 0)
                matrix[i][j] = 0;
        }
    }

    if (needhandlefirstRow)
    {
        for (int i = 0; i != colsize; ++i)
            matrix[0][i] = 0;
    }

    if (needhandlefirstCol)
    {
        for (int i = 0; i != rowsize; ++i)
            matrix[i][0] = 0;
    }
}
