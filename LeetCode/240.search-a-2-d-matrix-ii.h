// Tags:
// divide-and-conquer

// Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

// Integers in each row are sorted in ascending from left to right.
// Integers in each column are sorted in ascending from top to bottom.
// Example:

// Consider the following matrix:

// [
//   [1,   4,  7, 11, 15],
//   [2,   5,  8, 12, 19],
//   [3,   6,  9, 16, 22],
//   [10, 13, 14, 17, 24],
//   [18, 21, 23, 26, 30]
// ]
// Given target = 5, return true.

// Given target = 20, return false

// 剑指Offer 04

#include <iostream>
#include <vector>

using namespace std;

bool searchMatrix(vector<vector<int>> &matrix, int target);

void TestSearchMatrixII()
{
    vector<vector<int>> matrix = {
        {1, 4, 7, 11, 15},
        {2, 5, 8, 12, 19},
        {3, 6, 9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}};

    int target = 31;

    // vector<vector<int>> matrix = {
    //     {4}};
    // int target = 4;

    bool result = searchMatrix(matrix, target);
    cout << "Result is " << result << endl;
}

// // Version: divide and conquer
// bool searchMatrix(vector<vector<int>> &matrix, int left, int right, int top, int down, int target);
// bool searchMatrix(vector<vector<int>> &matrix, int target)
// {
//     if (matrix.empty() || matrix[0].empty())
//         return false;
//     return searchMatrix(matrix, 0, matrix[0].size() - 1, 0, matrix.size() - 1, target);
// }

// bool searchMatrix(vector<vector<int>> &matrix, int left, int right, int top, int down, int target)
// {

//     if (left > right || down < top)
//         return false;

//     if (left == right && top == down)
//         return matrix[top][left] == target;

//     int middleVertical = (left + right) / 2, middleHorizontal = (top + down) / 2;
//     int middleValue = matrix[middleHorizontal][middleVertical];

//     if (middleValue == target)
//         return true;

//     if (target < middleValue)
//     {
//         return searchMatrix(matrix, left, middleVertical, top, middleHorizontal, target) || // topLeft
//                searchMatrix(matrix, middleVertical + 1, right, top, middleHorizontal, target) || // topRight
//                searchMatrix(matrix, left, middleVertical, middleHorizontal + 1, down, target); // downLeft
//     }
//     else
//     {
//         return searchMatrix(matrix, middleVertical + 1, right, middleHorizontal + 1, down, target) || // downRight
//                searchMatrix(matrix, middleVertical + 1, right, top, middleHorizontal, target) || // topRight
//                searchMatrix(matrix, left, middleVertical, middleHorizontal + 1, down, target); // downLeft
//     }

//     return false;
// }

// Version: comparing with top-right
bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    if (matrix.empty() || matrix[0].empty())
        return false;

    int height = matrix.size() - 1, width = matrix[0].size() - 1, i = width, j = 0;
    while (i >= 0 && j <= height)
    {
        int value = matrix[j][i];
        if (value == target)
            return true;
        target > value ? j++ : i--;
    }
    return false;
}
