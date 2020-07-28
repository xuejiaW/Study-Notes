// 打乱数组

// 难度：中等

// Tags：
// Array

// 打乱一个没有重复元素的数组。

#include "parser.h"
#include "debug.h"

class Solution
{
public:
    Solution(vector<int> &nums) : backUp(nums)
    {
        vecSize = nums.size();
    }

    vector<int> reset()
    {
        return backUp;
    }

    vector<int> shuffle()
    {
        vector<int> nums = backUp;
        for (int i = 0; i != vecSize; ++i)
        {
            swap(nums[i], nums[i + rand() % (vecSize - i)]);
        }
        return nums;
    }

private:
    vector<int> backUp;
    int vecSize;
};

void TestShuffle()
{
    vector<int> nums{1, 2, 3, 4};
    Solution sol(nums);
    DebugVector(sol.shuffle());
    cout << endl;
    DebugVector(sol.reset());
}
