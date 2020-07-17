// 长度最小的子数组

// 难度：中等

// Tags：
// array | two-pointers| binary-search

// 给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的 连续 子数组，并返回其长度。如果不存在符合条件的子数组，返回 0。

// 示例：

// 输入：s = 7, nums = [2,3,1,2,4,3]
// 输出：2
// 解释：子数组 [4,3] 是该条件下的长度最小的子数组。

#include "parser.h"
#include "debug.h"

int minSubArrayLen(int s, vector<int> &nums);

void TestMinSubArray()
{
    vector<int> nums{2, 3, 1, 2, 4, 3};
    cout << minSubArrayLen(7, nums);
}

// // Version: two-pointer
// int minSubArrayLen(int s, vector<int> &nums)
// {
//     int numsSize = nums.size();
//     if (numsSize == 0)
//         return 0;

//     int result = INT_MAX;
//     int left = 0, right = 0;
//     int sum = nums[0];

//     while (right != numsSize)
//     {
//         if (sum < s)
//         {
//             if (++right != numsSize)
//                 sum += nums[right];
//         }
//         else
//         {
//             result = min(result, right - left + 1);
//             sum -= nums[left++];
//         }
//     }
//     return result == INT_MAX ? 0 : result;
// }

// Version : binary search
int minSubArrayLen(int s, vector<int> &nums)
{
    vector<int> sumVec(nums.size() + 1, 0);
    sumVec[0] = 0;

    int result = INT_MAX;
    int sum = 0;
    for (int i = 0; i != nums.size(); ++i)
    {
        sum += nums[i];
        sumVec[i + 1] = sum;
        int pos = -1, target = sumVec[i + 1] - s;

        // binary search
        int begin = 0, end = i;
        while (begin <= end)
        {
            int middle = (begin + end) / 2;
            if (sumVec[middle] > target)
                end = middle - 1;
            else
            {
                pos = middle;
                begin = middle + 1;
            }
        }

        if (pos != -1)
            result = min(result, i - pos + 1);
    }

    return result == INT_MAX ? 0 : result;
}