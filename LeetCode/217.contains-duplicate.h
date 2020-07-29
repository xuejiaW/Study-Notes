// 存在重复元素

// 难度：简单

// Tags
// array | hash-table

// 给定一个整数数组，判断是否存在重复元素。

// 如果任意一值在数组中出现至少两次，函数返回 true 。如果数组中每个元素都不相同，则返回 false 。

// 示例 1:

// 输入: [1,2,3,1]
// 输出: true

// 示例 2:

// 输入: [1,2,3,4]
// 输出: false

#include "parser.h"
#include "debug.h"
#include <unordered_set>

bool containsDuplicate(vector<int> &nums);

void TestContainsDeplicate()
{
    vector<int> nums{1, 2, 3, 1};
    cout << containsDuplicate(nums) << endl;
}

bool containsDuplicate(vector<int> &nums)
{
    unordered_set<int> existedNums;
    for (int i = 0; i != nums.size(); ++i)
    {
        if (existedNums.find(nums[i]) != existedNums.end())
            return true;
        existedNums.insert(nums[i]);
    }
    return false;
}
