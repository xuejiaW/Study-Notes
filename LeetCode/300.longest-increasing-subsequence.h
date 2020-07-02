// 最长上升子序列

// 难度：中等

// Tags
// greedy | binary-search | dynamic-programming

// 给定一个无序的整数数组，找到其中最长上升子序列的长度。

// 示例:

// 输入: [10,9,2,5,3,7,101,18]
// 输出: 4 
// 解释: 最长的上升子序列是 [2,3,7,101]，它的长度是 4。

#include "parser.h"
#include "debug.h"
#include <algorithm>

int lengthOfLIS(vector<int> &nums);
void TestLengthOfLTS()
{
    vector<int> nums{10, 9, 2, 5, 3, 7, 101, 18};
    int result = lengthOfLIS(nums);
    cout << result << endl;
}

// // Version: dynamic programming, O(n^2)
// int lengthOfLIS(vector<int> &nums)
// {
//     if (nums.empty())
//         return 0;

//     vector<int> valueTimes;
//     int totalMaxTimes = 0;
//     for (int i = 0; i != nums.size(); ++i)
//     {
//         int currMaxTimes = 0;
//         for (int j = 0; j != i; ++j)
//         {
//             if (nums[j] < nums[i] && valueTimes[j] > currMaxTimes)
//                 currMaxTimes = valueTimes[j];
//         }
//         valueTimes.push_back(currMaxTimes + 1);
//         totalMaxTimes = max(totalMaxTimes, currMaxTimes + 1);
//     }

//     return totalMaxTimes;
// }

// Version: greedy algorithm and binary search
int lengthOfLIS(vector<int> &nums)
{
    if (nums.empty())
        return 0;

    vector<int> currLIS;
    currLIS.push_back(nums[0]);

    for (int i = 1; i != nums.size(); ++i)
    {
        if (nums[i] > currLIS[currLIS.size() - 1])
        {
            currLIS.push_back(nums[i]);
        }
        else
        {
            //binary search for the last element smaller than nums[i]
            int begin = 0, end = currLIS.size() - 1, middle = (begin + end) / 2;
            int pos = -1;
            while (begin <= end)
            {
                middle = (begin + end) / 2;
                if (nums[i] > currLIS[middle])
                {
                    pos = middle;
                    begin = middle + 1;
                }
                else
                {
                    end = middle - 1;
                }
            }
            currLIS[pos + 1] = nums[i];
        }
    }

    return currLIS.size();
}