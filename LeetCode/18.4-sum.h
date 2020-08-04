// 四数之和

// 难度：中等

// Tags: 

// array | two-pointers

// 给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。

// 注意：

// 答案中不可以包含重复的四元组。

// 给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。

// 满足要求的四元组集合为：
// [
//   [-1,  0, 0, 1],
//   [-2, -1, 1, 2],
//   [-2,  0, 0, 2]
// ]

#include "parser.h"
#include "debug.h"

vector<vector<int>> fourSum(vector<int> &nums, int target);

void TestFourSum()
{
    vector<int> nums{1, 0, -1, 0, -2, 2};
    vector<vector<int>> result = fourSum(nums, 0);
    DebugVectorArray(result);
}

// Version: three pointer
vector<vector<int>> fourSum(vector<int> &nums, int target)
{
    vector<vector<int>> result;

    int numsSize = nums.size();
    if (numsSize < 4)
        return result;

    sort(nums.begin(), nums.end());

    for (int i = 0; i < numsSize - 3; ++i)
    {
        int leftVal = nums[i];
        for (int j = numsSize - 1; j > i + 1; j--)
        {
            int rightVal = nums[j];

            int innerLeft = i + 1, innerRight = j - 1;
            while (innerLeft < innerRight)
            {
                int innerLeftVal = nums[innerLeft], innerRightVal = nums[innerRight];
                int sum = leftVal + innerLeftVal + innerRightVal + rightVal;

                if (sum > target)
                    innerRight--;
                else if (sum < target)
                    innerLeft++;
                else
                {
                    result.push_back({leftVal, innerLeftVal, innerRightVal, rightVal});
                    while (innerLeft < innerRight && nums[innerRight] == innerRightVal)
                        innerRight--;
                    while (innerLeft < innerRight && nums[innerLeft] == innerLeftVal)
                        innerLeft++;
                }
            }

            while (j > i + 1 && nums[j - 1] == nums[j])
                j--;
        }

        while (i < numsSize - 1 && nums[i + 1] == nums[i])
            i++;
    }

    return result;
}

// // Version: with min/max optimization
// vector<vector<int>> fourSum(vector<int> &nums, int target)
// {
//     vector<vector<int>> result;

//     int numsSize = nums.size();
//     if (numsSize < 4)
//         return result;

//     sort(nums.begin(), nums.end());

//     for (int i = 0; i < numsSize - 3; ++i)
//     {
//         int minVal = nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3];
//         if (minVal > target)
//             continue;

//         int maxVal = nums[i] + nums[numsSize - 1] + nums[numsSize - 2] + nums[numsSize - 3];
//         if (maxVal < target)
//             continue;

//         int leftVal = nums[i];
//         for (int j = numsSize - 1; j > i + 1; j--)
//         {
//             int rightVal = nums[j];

//             int innerLeft = i + 1, innerRight = j - 1;
//             while (innerLeft < innerRight)
//             {
//                 int innerLeftVal = nums[innerLeft], innerRightVal = nums[innerRight];
//                 int sum = leftVal + innerLeftVal + innerRightVal + rightVal;

//                 if (sum > target)
//                     innerRight--;
//                 else if (sum < target)
//                     innerLeft++;
//                 else
//                 {
//                     result.push_back({leftVal, innerLeftVal, innerRightVal, rightVal});
//                     while (innerLeft < innerRight && nums[innerRight] == innerRightVal)
//                         innerRight--;
//                     while (innerLeft < innerRight && nums[innerLeft] == innerLeftVal)
//                         innerLeft++;
//                 }
//             }

//             while (j > i + 1 && nums[j - 1] == nums[j])
//                 j--;
//         }

//         while (i < numsSize - 1 && nums[i + 1] == nums[i])
//             i++;
//     }

//     return result;
// }
