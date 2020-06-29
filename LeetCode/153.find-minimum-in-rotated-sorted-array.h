// Tags
// array | binary-search

// 假设按照升序排序的数组在预先未知的某个点上进行了旋转。

// ( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

// 请找出其中最小的元素。

// 你可以假设数组中不存在重复元素。

// 示例 1:

// 输入: [3,4,5,1,2]
// 输出: 1
// 示例 2:

// 输入: [4,5,6,7,0,1,2]
// 输出: 0

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int findMin(vector<int> &nums);

void TestFindMinInRotatedSortedArray()
{
    vector<int> nums = {3, 4, 5, 1, 2};
    int result = findMin(nums);
    cout << "result is " << result << endl;
}

// // Version: binary-search
// int findMin(vector<int> &nums)
// {
//     if (nums.empty())
//         return 0;

//     int begin = 0, end = nums.size() - 1, middle = 0;
//     int result = INT_MAX;
//     while (begin < end)
//     {
//         middle = (begin + end) / 2;
//         if (nums[begin] < nums[middle]) // left part is ordered
//         {
//             result = min(result, nums[begin]);
//             begin = middle + 1;
//         }
//         else
//         {
//             result = min(result, nums[middle + 1]);
//             end = middle;
//         }
//     }

//     if (begin == end)
//         result = min(result, nums[begin]);

//     return result;
// }

// Version: more concise
int findMin(vector<int> &nums)
{
    if (nums.empty())
        return 0;
    int begin = 0, end = nums.size() - 1, middle = 0;
    while (begin < end)
    {
        middle = (begin + end) / 2;
        if (nums[middle] < nums[end])
            end = middle;
        else
            begin = middle + 1;
    }
    return nums[begin];
}