// 全排列

// 难度：中等

// Tags：
// back-tracking

// 给定一个 没有重复 数字的序列，返回其所有可能的全排列。

// 示例:

// 输入: [1,2,3]
// 输出:
// [
//   [1,2,3],
//   [1,3,2],
//   [2,1,3],
//   [2,3,1],
//   [3,1,2],
//   [3,2,1]
// ]

#include <vector>
#include <iostream>
using namespace std;

vector<vector<int>> permute(vector<int> &nums);
void TestPermutations()
{
    vector<int> nums{1, 2, 3};
    vector<vector<int>> result = permute(nums);

    for (auto vec : result)
    {
        for (auto i : vec)
        {
            cout << i << " ";
        }
        cout << endl;
    }
}

void permute(vector<vector<int>> &result, vector<int> &nums, int fix);

vector<vector<int>> permute(vector<int> &nums)
{
    vector<vector<int>> result;
    permute(result, nums, 0);

    return result;
}

void permute(vector<vector<int>> &result, vector<int> &nums, int fix)
{
    if (fix == nums.size())
    {
        result.push_back(nums);
        return;
    }

    for (int i = fix; i != nums.size(); ++i)
    {
        swap(nums[fix], nums[i]);
        permute(result, nums, fix + 1);
        swap(nums[fix], nums[i]);
    }
}
