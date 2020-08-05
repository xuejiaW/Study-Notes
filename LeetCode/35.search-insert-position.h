// 搜索插入位置

// 难度：简单

// Tags
// array | binary-search

// 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

// 你可以假设数组中无重复元素。

// 示例 1:

// 输入: [1,3,5,6], 5
// 输出: 2
// 示例 2:

// 输入: [1,3,5,6], 2
// 输出: 1
// 示例 3:

// 输入: [1,3,5,6], 7
// 输出: 4
// 示例 4:

// 输入: [1,3,5,6], 0
// 输出: 0

#include "parser.h"
#include "debug.h"

int searchInsert(vector<int> &nums, int target);
void TestSearchInsert()
{
    vector<int> nums{1, 3, 5, 6};
    cout << searchInsert(nums, 5); //2
}

int searchInsert(vector<int> &nums, int target)
{
    int numsSize = nums.size();
    int left = 0, right = numsSize - 1, toInsert = numsSize;

    while (left <= right)
    {
        int middle = (left + right) / 2;
        if (nums[middle] < target)
        {
            left = middle + 1;
        }
        else
        {
            toInsert = middle;
            right = middle - 1;
        }
    }
    return toInsert;
}
