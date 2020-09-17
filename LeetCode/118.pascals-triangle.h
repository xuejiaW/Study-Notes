//  [118] 杨辉三角

//  https://leetcode-cn.com/problems/pascals-triangle/description/

//  algorithms
//  Easy (67.39%)

// Tags
// array

//  给定一个非负整数 numRows，生成杨辉三角的前 numRows 行。

//  在杨辉三角中，每个数是它左上方和右上方的数的和。

//  示例:

//  输入: 5
//  输出:
//  [
//  ⁠    [1],
//  ⁠   [1,1],
//  ⁠  [1,2,1],
//  ⁠ [1,3,3,1],
//  ⁠[1,4,6,4,1]
//  ]



// @lc code=start
#include "parser.h"
#include "debug.h"

vector<vector<int>> generate(int numRows);

void TestGenerate()
{
    vector<vector<int>> result = generate(3);
    DebugVectorArray(result);
}

vector<vector<int>> generate(int numRows)
{
    vector<vector<int>> result;
    if (numRows == 0)
        return result;

    result.push_back(vector<int>{1});

    int row = 0;
    while (row < numRows - 1)
    {
        int levelNum = result[result.size() - 1].size();
        vector<int> rowVec;
        rowVec.push_back(1);
        for (int i = 1; i < levelNum; ++i)
        {
            rowVec.push_back(result[row][i - 1] + result[row][i]);
        }
        rowVec.push_back(1);
        result.push_back(rowVec);
        row++;
    }

    return result;
}
// @lc code=end
