// 跳跃游戏

// 难度：中等

// Tags
// array | greedy

// 给定一个非负整数数组，你最初位于数组的第一个位置。

// 数组中的每个元素代表你在该位置可以跳跃的最大长度。

// 判断你是否能够到达最后一个位置。

// 示例 1:
// 输入: [2,3,1,1,4]
// 输出: true
// 解释: 我们可以先跳 1 步，从位置 0 到达 位置 1, 然后再从位置 1 跳 3 步到达最后一个位置。

// 示例 2:
// 输入: [3,2,1,0,4]
// 输出: false
// 解释: 无论怎样，你总会到达索引为 3 的位置。但该位置的最大跳跃长度是 0 ， 所以你永远不可能到达最后一个位置。

#include "parser.h"
#include "debug.h"
#include <algorithm>

bool canJump(vector<int> &nums);
void TestCanJump()
{
    // vector<int> nums{2, 3, 1, 1, 4};
    vector<int> nums{3, 2, 1, 0, 4};
    bool result = canJump(nums);
    cout << result << endl;
}

// // Version: like dp,O(n^2). from end to begin
// bool canJump(vector<int> &nums)
// {
//     int size = nums.size();
//     if (size == 0)
//         return true;
//     if (size == 1)
//         return true;

//     vector<bool> canJump = vector<bool>(size, false);
//     canJump[size - 1] = true;

//     for (int i = size - 2; i >= 0; i--)
//     {
//         for (int j = nums[i]; j > 0; --j)
//         {
//             if (i + j >= (size - 1) || canJump[i + j])
//             {
//                 canJump[i] = true;
//                 break;
//             }
//         }
//     }

//     return canJump[0];
// }

// version: greedy, from begin to end
bool canJump(vector<int> &nums)
{
    int currMax = 0, numsSize = nums.size();

    for (int i = 0; i != numsSize; ++i)
    {
        if (i > currMax)
            return false;
        currMax = max(currMax, i + nums[i]);
    }

    return true;
}