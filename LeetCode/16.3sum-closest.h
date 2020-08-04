// 最接近的三数之和

// 难度：中等

// Tags：
// array | two-pointers

// 给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。

 

// 示例：

// 输入：nums = [-1,2,1,-4], target = 1
// 输出：2
// 解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2) 。

#include "parser.h"
#include "debug.h"

int threeSumClosest(vector<int> &nums, int target);

void TestThreeSumClosest()
{
    vector<int> nums{-1, 2, 1, -4};
    cout << threeSumClosest(nums, 1);
}

int threeSumClosest(vector<int> &nums, int target)
{
    int numsSize = nums.size();
    if (numsSize < 3)
        return 0;

    sort(nums.begin(), nums.end());

    int delta = INT_MAX;
    int result = -1;

    for (int i = 0; i < numsSize - 1; ++i)
    {
        int left = i + 1, right = numsSize - 1;
        while (left < right)
        {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum > target)
                right--;
            else if (sum < target)
                left++;

            int currDelta = abs(sum - target);
            if (currDelta == 0)
                return sum;

            if (currDelta < delta)
            {
                result = sum;
                delta = currDelta;
            }
        }

        while (i < numsSize - 1 && nums[i + 1] == nums[i])
            i++;
    }

    return result;
}
