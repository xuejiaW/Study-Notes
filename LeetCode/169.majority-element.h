// Tags:
// array | hash-table | sorting

// Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

// You may assume that the array is non-empty and the majority element always exist in the array.

// Example 1:

// Input: [3,2,3]
// Output: 3
// Example 2:

// Input: [2,2,1,1,1,2,2]
// Output: 2

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
