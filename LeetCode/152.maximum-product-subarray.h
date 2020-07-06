// 乘积最大子数组

// 难度：中等

// Tags
// array | dynamic-programming

// 给你一个整数数组 nums ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

//  示例 1:

// 输入: [2,3,-2,4]
// 输出: 6
// 解释: 子数组 [2,3] 有最大乘积 6。

// 示例 2:

// 输入: [-2,0,-1]
// 输出: 0
// 解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。

#include "parser.h"
#include "debug.h"

int maxProduct(vector<int> &nums);

void TestMaxProduct()
{
    // vector<int> nums{2, 3, -2, 4};
    vector<int> nums{-2, -0, -1};
    int max = maxProduct(nums);
    cout << max << endl;
}

int maxProduct(vector<int> &nums)
{
    if (nums.empty())
        return 0;

    vector<pair<int, int>> minMaxVec(nums.size());
    minMaxVec[0] = {nums[0], nums[0]};
    int maxVal = nums[0];

    for (int i = 1; i != nums.size(); ++i)
    {
        int prevMinTimesCurr = minMaxVec[i - 1].first * nums[i], prevMaxTimesCurr = minMaxVec[i - 1].second * nums[i];
        int currMin = min(prevMinTimesCurr, min(prevMaxTimesCurr, nums[i]));
        int currMax = max(prevMinTimesCurr, max(prevMaxTimesCurr, nums[i]));
        maxVal = max(maxVal, currMax);
        minMaxVec[i] = {currMin, currMax};
    }
    return maxVal;
}
