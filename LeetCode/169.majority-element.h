// 多数元素

// 难度：简单

// 标签：
// 数组 | 哈希表

// 给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。

// 你可以假设数组是非空的，并且给定的数组总是存在多数元素。

// 示例 1:
// 输入: [3,2,3]
// 输出: 3

// 示例 2:
// 输入: [2,2,1,1,1,2,2]
// 输出: 2

#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int majorityElement(vector<int> &nums);

void TestMajorityElement()
{
    // vector<int> nums{3, 2, 3};
    vector<int> nums{2, 2, 1, 1, 1, 2, 2};
    // vector<int> nums;
    int result = majorityElement(nums);
    cout << "result is " << result << endl;
}

// // Version: use hash map
// int majorityElement(vector<int> &nums)
// {
//     int halfNumsSize = nums.size() / 2;

//     unordered_map<int, int> value2TimesMap;

//     for (const int &i : nums)
//     {
//         if (++value2TimesMap[i] > halfNumsSize)
//             return i;
//     }

//     return 0;
// }

// // Version: use sort
// int majorityElement(vector<int> &nums)
// {
//     sort(nums.begin(), nums.end());
//     return nums[nums.size() / 2];
// }

// // Version: use voting
int majorityElement(vector<int> &nums)
{
    int winner = 0, counter = 0;
    for (const int &i : nums)
    {
        if (!counter)
            winner = i;
        counter += winner == i ? 1 : -1;
    }
    return winner;
}
