// Tags:
// array | divide-and-conquer

// Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

// Example:

// Input: [-2,1,-3,4,-1,2,1,-5,4],
// Output: 6
// Explanation: [4,-1,2,1] has the largest sum = 6.

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
