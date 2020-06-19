// 搜索旋转排序数组

// 难度：中等

// Tags:
// array | binary-search

// 假设按照升序排序的数组在预先未知的某个点上进行了旋转。

// ( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

// 搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。

// 你可以假设数组中不存在重复的元素。

// 你的算法时间复杂度必须是 O(log n) 级别。

// 示例 1:

// 输入: nums = [4,5,6,7,0,1,2], target = 0
// 输出: 4

// 示例 2:

// 输入: nums = [4,5,6,7,0,1,2], target = 3
// 输出: -1


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