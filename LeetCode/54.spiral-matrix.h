// 螺旋矩阵

// 难度：中等

// Tags
// array

// 给定一个包含 m x n 个元素的矩阵（m 行, n 列），请按照顺时针螺旋顺序，返回矩阵中的所有元素。

// 示例 1:

// 输入:
// [
//  [ 1, 2, 3 ],
//  [ 4, 5, 6 ],
//  [ 7, 8, 9 ]
// ]
// 输出: [1,2,3,6,9,8,7,4,5]

// 示例 2:

// 输入:
// [
//   [1, 2, 3, 4],
//   [5, 6, 7, 8],
//   [9,10,11,12]
// ]
// 输出: [1,2,3,4,8,12,11,10,9,5,6,7]

#include <iostream>
#include <vector>
#include <unordered_map>
#include <iterator>

using namespace std;

vector<int> spiralOrder(vector<vector<int>> &matrix);

void TestSpiralOrder()
{
    // vector<vector<int>> matrix = {
    //     {1, 2, 3},
    //     {4, 5, 6},
    //     {7, 8, 9}};

    vector<vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};

    vector<int> result = spiralOrder(matrix);

    for (int i : result)
        cout << i << " " << endl;
}


// Version: directly moving
vector<int> spiralOrder(vector<vector<int>> &matrix)
{
    vector<int> result;

    if (matrix.empty())
        return result;

    int rowLowEdge = matrix.size() - 1, colRightEdge = matrix[0].size() - 1, rowHighEdge = 0, colLeftEdge = 0;
    int size = (rowLowEdge + 1) * (colRightEdge + 1);

    // 0 -> right; 1 -> down; 2 -> right; 3 -> up
    int state = 0;
    int currRow = 0, currCol = 0;

    while (size-- > 0)
    {
        result.push_back(matrix[currRow][currCol]);

        if (state == 0)
            currCol + 1 > colRightEdge ? (state = 1, ++rowHighEdge, ++currRow) : ++currCol;
        else if (state == 1)
            currRow + 1 > rowLowEdge ? (state = 2, --colRightEdge, --currCol) : ++currRow;
        else if (state == 2)
            currCol - 1 < colLeftEdge ? (state = 3, --rowLowEdge, --currRow) : --currCol;
        else if (state == 3)
            currRow - 1 < rowHighEdge ? (state = 0, ++colLeftEdge, ++currCol) : --currRow;
    }

    return result;
}

