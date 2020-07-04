// 子集

// 难度：中等

// Tags
// array | backtracking | bit-manipulation

// 给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。

// 说明：解集不能包含重复的子集。

// 示例:

// 输入: nums = [1,2,3]
// 输出:
// [
//   [3],
//   [1],
//   [2],
//   [1,2,3],
//   [1,3],
//   [2,3],
//   [1,2],
//   []
// ]

#include "parser.h"
#include "debug.h"

vector<vector<int>> subsets(vector<int> &nums);
void TestSubsets()
{
    vector<int> nums{1, 2, 3};
    vector<vector<int>> result = subsets(nums);
    DebugVectorArray(result);
}

// // Version: like dp
// vector<vector<int>> subsets(vector<int> &nums)
// {
//     vector<vector<int>> result;
//     result.push_back(vector<int>());

//     for (int i = 0; i != nums.size(); ++i)
//     {
//         int size = result.size();
//         for (int j = 0; j != size; ++j)
//         {
//             vector<int> sol = result[j];
//             sol.push_back(nums[i]);
//             result.push_back(sol);
//         }
//     }

//     return result;
// }

// Version: back tracking
void backTracking(vector<vector<int>> &result, vector<int> &sol, const vector<int> &nums, int start);
vector<vector<int>> subsets(vector<int> &nums)
{
    vector<vector<int>> result;
    vector<int> sol;
    backTracking(result, sol, nums, 0);
    return result;
}

void backTracking(vector<vector<int>> &result, vector<int> &sol, const vector<int> &nums, int start)
{
    result.push_back(sol);
    for (int i = start; i != nums.size(); ++i)
    {
        sol.push_back(nums[i]);
        backTracking(result, sol, nums, i + 1);
        sol.pop_back();
    }
}