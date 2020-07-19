// 找到所有数组中消失的数字

// 难度：
// 简单

// Tags
// array

// 给定一个范围在  1 ≤ a[i] ≤ n ( n = 数组大小 ) 的 整型数组，数组中的元素一些出现了两次，另一些只出现一次。

// 找到所有在 [1, n] 范围之间没有出现在数组中的数字。

// 您能在不使用额外空间且时间复杂度为O(n)的情况下完成这个任务吗? 你可以假定返回的数组不算在额外空间内。

// 示例:

// 输入:
// [4,3,2,7,8,2,3,1]

// 输出:
// [5,6]

#include "parser.h"
#include "debug.h"

vector<int> findDisappearedNumbers(vector<int> &nums);

void TestFindDisappearNumbers()
{
    vector<int> nums = vector<int>{4, 3, 2, 7, 8, 2, 3, 1};
    vector<int> result = findDisappearedNumbers(nums);
    DebugVector(result);
}

vector<int> findDisappearedNumbers(vector<int> &nums)
{
    vector<int> result;
    for (int i = 0; i != nums.size(); ++i)
    {
        int targetIndex = abs(nums[i]) - 1;
        if (nums[targetIndex] > 0)
            nums[targetIndex] *= -1;
    }

    for (int i = 0; i != nums.size(); ++i)
    {
        if (nums[i] > 0)
            result.push_back(i + 1);
    }
    return result;
}
