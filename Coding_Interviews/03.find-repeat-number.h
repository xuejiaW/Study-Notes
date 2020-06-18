// Tags:
// array | hash-map | swap

// 找出数组中重复的数字。


// 在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。

// 示例 1：

// 输入：
// [2, 3, 1, 0, 2, 5, 3]
// 输出：2 或 3 


#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int findRepeatNumber(vector<int> &nums);

void TestFindRepeatNumber()
{
    vector<int> nums{2, 3, 1, 0, 2, 5, 3};
    int result = findRepeatNumber(nums);
    cout << "result is " << result;
}

// // Version: hash-map
// int findRepeatNumber(vector<int> &nums)
// {
//     unordered_set<int> existedNums;
//     for (const int &i : nums)
//     {
//         if (existedNums.find(i) != existedNums.end())
//             return i;
//         existedNums.insert(i);
//     }
//     return 0;
// }

// Version: swap
// Because there are n numbers and number's range is from 0 ~ n-1
// So if there is no repeat number, every number can at their own position
// e.g value 3 is at index 3, value 0 is at index 0
int findRepeatNumber(vector<int> &nums)
{
    for (int i = 0; i != nums.size(); ++i)
    {
        while (nums[i] != i)
        {
            if (nums[i] == nums[nums[i]])
                return nums[i];
            else
                swap(nums[i], nums[nums[i]]);
        }
    }
    return 0;
}