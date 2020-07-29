// 存在重复元素 II

// 难度：简单

// Tags
// array | hash-table

// 给定一个整数数组和一个整数 k，判断数组中是否存在两个不同的索引 i 和 j，使得 nums [i] = nums [j]，并且 i 和 j 的差的 绝对值 至多为 k。

// 示例 1:
// 输入: nums = [1,2,3,1], k = 3
// 输出: true

// 示例 2:
// 输入: nums = [1,0,1,1], k = 1
// 输出: true

// 示例 3:
// 输入: nums = [1,2,3,1,2,3], k = 2
// 输出: false

#include "parser.h"
#include "debug.h"
#include <unordered_map>

bool containsNearbyDuplicate(vector<int> &nums, int k);

void TestContainsNearByDuplicate()
{
    vector<int> nums{1, 2, 3, 1, 2, 3};
    cout << containsNearbyDuplicate(nums, 2);
}

bool containsNearbyDuplicate(vector<int> &nums, int k)
{
    unordered_map<int, int> val2LastIndexMap;

    for (int i = 0; i != nums.size(); ++i)
    {
        if (val2LastIndexMap.find(nums[i]) != val2LastIndexMap.end())
        {
            if (i - val2LastIndexMap[nums[i]] <= k)
                return true;
        }

        val2LastIndexMap[nums[i]] = i; // has recordbut gap >= k or no record
    }

    return false;
}
