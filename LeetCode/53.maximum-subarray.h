// 最大子序和

// 难度：简单

// Tags:
// array | divide-and-conquer

// 给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

// 示例:

// 输入: [-2,1,-3,4,-1,2,1,-5,4],
// 输出: 6
// 解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxSubArray(vector<int> &nums);
int getMaxCrossArray(vector<int> &nums, int begin, int end);
int getMaxSubArray(vector<int> &nums, int begin, int end);

void TestMaxSubArray()
{
    // vector<int> test{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    vector<int> test{1, 2, -1};
    int result = maxSubArray(test);
    cout << endl;
    cout << "result is " << result << endl;
}

int maxSubArray(vector<int> &nums)
{
    return getMaxSubArray(nums, 0, nums.size() - 1);
}

int getMaxSubArray(vector<int> &nums, int begin, int end)
{
    if (begin == end)
        return nums[begin];

    int length = end - begin;
    int middleIt = begin + length / 2;

    int leftHalfResult = getMaxSubArray(nums, begin, middleIt);
    int crossResult = getMaxCrossArray(nums, begin, end);
    int rightHalfrResult = getMaxSubArray(nums, middleIt + 1, end);

    int result = max(leftHalfResult, crossResult);
    result = max(result, rightHalfrResult);

    return result;
}

int getMaxCrossArray(vector<int> &nums, int begin, int end)
{
    int length = end - begin;
    int middleIt = begin + length / 2;

    int sum = 0, maxLeftPartSum = INT_MIN, maxRightPartSum = INT_MIN;

    for (int it = middleIt; it >= begin; --it)
    {
        sum += nums[it];
        maxLeftPartSum = max(sum, maxLeftPartSum);
    }

    sum = 0;
    for (int it = middleIt + 1; it <= end; ++it)
    {
        sum += nums[it];
        maxRightPartSum = max(sum, maxRightPartSum);
    }

    return maxLeftPartSum + maxRightPartSum;
}
