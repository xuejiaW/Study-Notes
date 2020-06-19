// Tags: 
// DFS | BFS

// 剑指 Offer 13. 机器人的运动范围

// 地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），也不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？

//  

// 示例 1：

// 输入：m = 2, n = 3, k = 1
// 输出：3
// 示例 2：

// 输入：m = 3, n = 1, k = 0
// 输出：1
// 提示：

// 1 <= n,m <= 100
// 0 <= k <= 20

#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

int movingCount(int rowNum, int colNum, int limit);

void TestMovingCount()
{
    // int result = movingCount(2, 3, 1);
    int result = movingCount(3, 2, 17);
    cout << "result is " << result << endl;
}

int getDigitSum(int val)
{
    int sum = 0;
    while (val != 0)
    {
        sum += val % 10;
        val /= 10;
    }
    return sum;
}

//Version: Depth First Searching

int movingCount(vector<vector<bool>> &touched, const int &row, const int &col,
                const int &rowNum, const int &colNum, const int &limit);

int movingCount(int rowNum, int colNum, int limit)
{
    if (limit == 0)
        return 1;
    vector<vector<bool>> searched(rowNum, vector<bool>(colNum, false));
    return movingCount(searched, 0, 0, rowNum, colNum, limit);
}

int movingCount(vector<vector<bool>> &touched, const int &row, const int &col,
                const int &rowNum, const int &colNum, const int &limit)
{
    if (row < 0 || row >= rowNum || col < 0 || col >= colNum || touched[row][col] ||
        (getDigitSum(row) + getDigitSum(col) > limit))
        return 0;

    touched[row][col] = true;

    // Only should move right and down
    int result = 1 + movingCount(touched, row, col + 1, rowNum, colNum, limit) + // right
                 movingCount(touched, row + 1, col, rowNum, colNum, limit);      // down
    return result;
}

// // Version: Breadth First Searching
// int movingCount(int rowNum, int colNum, int limit)
// {
//     if (limit == 0)
//         return 1;

//     queue<pair<int, int>> waitingToTouch;
//     vector<vector<bool>> searched(rowNum, vector<bool>(colNum, false));

//     waitingToTouch.push({0, 0});
//     searched[0][0] = true;

//     int num = 0;

//     while (!waitingToTouch.empty())
//     {
//         ++num;
//         int row = waitingToTouch.front().first, col = waitingToTouch.front().second;
//         waitingToTouch.pop();

//         if ((row + 1) < rowNum && (getDigitSum(row + 1) + getDigitSum(col)) <= limit && !searched[row + 1][col])
//         {

//             searched[row + 1][col] = true; //To avoid duplicate adding
//             waitingToTouch.push({row + 1, col});
//         }

//         if ((col + 1) < colNum && (getDigitSum(row) + getDigitSum(col + 1)) <= limit && !searched[row][col + 1])
//         {
//             searched[row][col + 1] = true;
//             waitingToTouch.push({row, col + 1});
//         }
//     }

//     return num;
// }
