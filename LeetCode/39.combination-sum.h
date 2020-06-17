// Tags:
// array | backtracking | dynamic programming

// Given a set of candidate numbers (candidates) (without duplicates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.

// The same repeated number may be chosen from candidates unlimited number of times.

// Note:

// All numbers (including target) will be positive integers.
// The solution set must not contain duplicate combinations.
// Example 1:

// Input: candidates = [2,3,6,7], target = 7,
// A solution set is:
// [
//   [7],
//   [2,2,3]
// ]
// Example 2:

// Input: candidates = [2,3,5], target = 8,
// A solution set is:
// [
//   [2,2,2,2],
//   [2,3,3],
//   [3,5]
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
        //e.g value = 2, i = 3, means trying get result for 3 by value 2 and existing result
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