// 数组中重复的数据

// 难度：中等

// Tags：

// Array

// 给定一个整数数组 a，其中1 ≤ a[i] ≤ n （n为数组长度）, 其中有些元素出现两次而其他元素出现一次。

// 找到所有出现两次的元素。

// 你可以不用到任何额外空间并在O(n)时间复杂度内解决这个问题吗？

// 示例：

// 输入:
// [4,3,2,7,8,2,3,1]

// 输出:
// [2,3]

#include "parser.h"
#include "debug.h"

vector<int> findDuplicates(vector<int> &nums);
void TestFindAllDuplicates()
{
    vector<int> nums{4, 3, 2, 7, 8, 2, 3, 1};
    vector<int> result = findDuplicates(nums);
    DebugVector(result);
}

vector<int> findDuplicates(vector<int> &nums)
{
    vector<int> result;
    int numsSize = nums.size();
    for (int i = 0; i != numsSize; ++i)
    {
        nums[(nums[i]-1) % numsSize] += numsSize;
    }

    for (int i = 0; i != numsSize; ++i)
    {
        if (nums[i] > 2 * numsSize)
            result.push_back(i+1);
    }
    return result;
}
