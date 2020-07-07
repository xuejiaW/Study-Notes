// 寻找重复数

// 难度：中等

// Tags
// array | two-pointers | binary-search

// 给定一个包含 n + 1 个整数的数组 nums，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。假设只有一个重复的整数，找出这个重复的数。

// 示例 1:
// 输入: [1,3,4,2,2]
// 输出: 2

// 示例 2:
// 输入: [3,1,3,4,2]
// 输出: 3
// 说明：

// 不能更改原数组（假设数组是只读的）。
// 只能使用额外的 O(1) 的空间。
// 时间复杂度小于 O(n2) 。
// 数组中只有一个重复的数字，但它可能不止重复出现一次。

#include "parser.h"
#include "debug.h"

int findDuplicate(vector<int> &nums);
void TestFindDuplicate()
{
    // vector<int> nums{1, 3, 4, 2, 2};
    vector<int> nums{3, 1, 3, 4, 2};
    cout << findDuplicate(nums);
}

// // Version: binary search
// int findDuplicate(vector<int> &nums)
// {
//     int left = 0, right = nums.size() - 1;
//     while (left < right)
//     {
//         int middle = (left + right) / 2;
//         int count = 0;
//         for (const int &i : nums)
//             count += (i <= middle);
//         if (count > middle)
//             right = middle;
//         else
//             left = middle + 1;
//     }
//     return left;
// }

// Version: cycle linked-list
int findDuplicate(vector<int> &nums)
{
    int point = 0;
    int slow = 0, fast = 0;

    while (true) // because must have cycle, so using infinite loop
    {
        slow = nums[slow];
        fast = nums[nums[fast]];
        if (slow == fast)
            break;
    }

    int third = 0;
    while (slow != third)
    {
        slow = nums[slow];
        third = nums[third];
    }
    return third;
}