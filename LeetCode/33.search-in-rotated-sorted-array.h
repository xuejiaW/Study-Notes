// Tags:
// array | binary-search

// Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

// (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).

// You are given a target value to search. If found in the array return its index, otherwise return -1.

// You may assume no duplicate exists in the array.

// Your algorithm's runtime complexity must be in the order of O(log n).

// Example 1:

// Input: nums = [4,5,6,7,0,1,2], target = 0
// Output: 4
// Example 2:

// Input: nums = [4,5,6,7,0,1,2], target = 3
// Output: -1

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int search(vector<int> &nums, int target);

void TestSearchInRotatedSortedArray()
{
    // vector<int> nums{4, 5, 6, 7, 0, 1, 2};
    // int target = 7;
    vector<int> nums{3, 1};
    int target = 1;
    int result = search(nums, target);
    cout << "result is " << result << endl;
}

// //Version: binary search with recursive
// int toSearch(vector<int> &nums, int begin, int end, int target);
// int search(vector<int> &nums, int target)
// {
//     if (nums.empty())
//         return -1;
//     return toSearch(nums, 0, nums.size() - 1, target);
// }

// int toSearch(vector<int> &nums, int begin, int end, int target)
// {
//     if (nums[begin] <= nums[end] && (target < nums[begin] || target > nums[end]))
//         return -1;

//     int middle = (begin + end) / 2;

//     if (nums[middle] == target)
//         return middle;

//     int result = toSearch(nums, begin, middle, target);

//     if (result == -1)
//         result = toSearch(nums, middle + 1, end, target);

//     return result;
// }

// Version: binary search without recursive
int search(vector<int> &nums, int target)
{
    if (nums.empty())
        return -1;

    int begin = 0, end = nums.size() - 1, middle = (begin + end) / 2;

    while (begin <= end)
    {
        middle = (begin + end) / 2;
        if (nums[middle] == target)
            return middle;

        if (nums[begin] <= nums[middle]) //left part is ordered
        {
            if (target >= nums[begin] && target <= nums[middle]) //target is in left ordered part
                end = middle - 1;
            else
                begin = middle + 1;
        }
        else //right part is ordered
        {
            if (target >= nums[middle] && target <= nums[end]) // target is in right ordered part
                begin = middle + 1;
            else
                end = middle - 1;
        }
    }
    return -1;
}