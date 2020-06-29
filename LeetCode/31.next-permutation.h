// 下一个排列

// 难度：中等

// Tags:
// 数组 | 数学

// 实现获取下一个排列的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。

// 如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

// 必须原地修改，只允许使用额外常数空间。

// 以下是一些例子，输入位于左侧列，其相应输出位于右侧列。
// 1,2,3 → 1,3,2
// 3,2,1 → 1,2,3
// 1,1,5 → 1,5,1

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void nextPermutation(vector<int> &nums);

void TestNextPermutation()
{
    vector<int> nums{5, 1, 1};
    nextPermutation(nums);
    for (auto i : nums)
        cout << i << " " << endl;
}

void nextPermutation(vector<int> &nums)
{
    int numsSize = nums.size();
    int revertPos = nums.size() - 2;
    while (revertPos >= 0 && nums[revertPos] >= nums[revertPos + 1])
        revertPos--;

    //from revertPos+1~end should be descending, turn to ascending
    reverse(nums.begin() + revertPos + 1, nums.end());

    if (revertPos >= 0)
    {
        for (int i = revertPos + 1; i != nums.size(); i++)
        {
            //find the first num that larger than nums[revertPos]
            if (nums[i] > nums[revertPos])
            {
                swap(nums[i], nums[revertPos]);
                break;
            }
        }
    }
}
