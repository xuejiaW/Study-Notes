// 组合总和

// 难度：中等

// Tags:
// array | backtracking | dynamic programming

// 给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

// candidates 中的数字可以无限制重复被选取。

// 说明：

// 所有数字（包括 target）都是正整数。
// 解集不能包含重复的组合。 

// 示例 1:

// 输入: candidates = [2,3,6,7], target = 7,
// 所求解集为:
// [
//   [7],
//   [2,2,3]
// ]

// 示例 2:

// 输入: candidates = [2,3,5], target = 8,
// 所求解集为:
// [
//   [2,2,2,2],
//   [2,3,3],
//   [3,5]
// ]

#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<vector<int>> combinationSum(vector<int> &candidates, int target);

void TestCombinationSum()
{
    // vector<int> candidates{2, 3, 6, 7};
    // int target = 7;
    vector<int> candidates{2, 3, 5};
    int target = 8;
    vector<vector<int>> result = combinationSum(candidates, target);
    for (vector<int> vec : result)
    {
        for (int i : vec)
            cout << i << " ";
        cout << endl;
    }
}

// // Version: backtracking
// void getCombinationSum(vector<int> &candidates, int startIndex, int target,
//                        vector<int> &solution, vector<vector<int>> &result);
// vector<vector<int>> combinationSum(vector<int> &candidates, int target)
// {
//     vector<vector<int>> result;

//     sort(candidates.begin(), candidates.end());

//     vector<int> solution;
//     getCombinationSum(candidates, 0, target, solution, result);

//     return result;
// }

// void getCombinationSum(vector<int> &candidates, int startIndex, int target,
//                        vector<int> &solution, vector<vector<int>> &result)
// {
//     if (target == 0)
//     {
//         result.push_back(solution);
//         return;
//     }

//     if (startIndex == candidates.size() || target < candidates[startIndex])
//         return;

//     solution.push_back(candidates[startIndex]);
//     getCombinationSum(candidates, startIndex, target - candidates[startIndex], solution, result);
//     solution.pop_back(); // return to the last state
//     getCombinationSum(candidates, startIndex + 1, target, solution, result);
// }

// Version: dynamic programming
vector<vector<int>> combinationSum(vector<int> &candidates, int target)
{
    sort(candidates.begin(), candidates.end());

    unordered_map<int, vector<vector<int>>> targetResultMap;
    targetResultMap[0].push_back(vector<int>()); //push back [0] to result for target 0

    for (const int &value : candidates)
    {
        //The results can be yielded with this value
        //e.g value = 2, i = 3, means trying get result for 3 by value 2 and existing result for (3-2)
        for (int i = value; i <= target; ++i)
        {
            if (targetResultMap[i - value].size() > 0) // has result
            {
                vector<vector<int>> result = targetResultMap[i - value];
                for (vector<int> &solution : result)
                    solution.push_back(value);
                targetResultMap[i].insert(targetResultMap[i].end(), result.begin(), result.end());
            }
        }
    }

    return targetResultMap[target];
}