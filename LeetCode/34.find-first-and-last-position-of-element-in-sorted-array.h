// 在排序数组中查找元素的第一个和最后一个位置

// 难度：中等

// Tags:
// array | binary search

// 给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

// 你的算法时间复杂度必须是 O(log n) 级别。

// 如果数组中不存在目标值，返回 [-1, -1]。

// 示例 1:

// 输入: nums = [5,7,7,8,8,10], target = 8
// 输出: [3,4]
// 示例 2:

// 输入: nums = [5,7,7,8,8,10], target = 6
// 输出: [-1,-1]

#include <vector>
#include <iostream>

using namespace std;

vector<int> searchRange(vector<int> &nums, int target);

void TestSearchRange()
{
    // vector<int> nums{5, 7, 7, 8, 8, 10};
    // vector<int> result = searchRange(nums, 10);
    vector<int> nums{5};
    vector<int> result = searchRange(nums, 5);
    for (auto i : result)
        cout << i << endl;
}


vector<int> searchRange(vector<int> &nums, int target)
{
    vector<int> result{-1, -1};
    if (nums.empty())
        return result;

    int begin = 0, end = nums.size() - 1, middle;
    while (begin <= end)
    {
        middle = (begin + end) / 2;
        if (nums[middle] == target)
        {
            int i = middle, j = middle;
            while (i >= begin && nums[i] == target)
                result[0] = i--;
            while (j <= end && nums[j] == target)
                result[1] = j++;

            break;
        }
        else if (nums[middle] < target)
            begin = middle + 1;
        else
            end = middle - 1;
    }

    return result;
}
