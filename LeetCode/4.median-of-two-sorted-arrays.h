// 寻找两个正序数组中的中位数

// 难度：困难

// Tags：
// array | binary - search

// 给定两个大小为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。

// 请你找出这两个正序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。

// 你可以假设 nums1 和 nums2 不会同时为空。

// 示例 1 :
// nums1 = [ 1, 3 ] nums2 = [2] 则中位数是 2.0

// 示例 2 : 
// nums1 = [ 1, 2 ] nums2 = [ 3, 4 ]
// 则中位数是(2 + 3) /2 = 2.5

#include "parser.h"
#include "debug.h"

             double findMedianSortedArrays(vector<int> & nums1, vector<int> &nums2);

void TestFindMedianSortedArrays()
{
    vector<int> nums1{1, 2}, nums2{3, 4};
    cout << findMedianSortedArrays(nums1, nums2);
}

// // Version: two pointer O(m+n)
// double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
// {
//     int nums1Size = nums1.size(), nums2Size = nums2.size();

//     int needNum = (nums1Size + nums2Size) % 2 == 1 ? 1 : 2;
//     int mid = (nums1Size + nums2Size) / 2 + 1;

//     int firstNum = 0, secNum = 0;
//     int nums1Ptr = 0, nums2Ptr = 0, moveCount = 0;

//     while (nums1Ptr < nums1Size || nums2Ptr < nums2Size)
//     {
//         firstNum = secNum;

//         if (nums2Ptr >= nums2Size || (nums1Ptr < nums1Size && nums1[nums1Ptr] <= nums2[nums2Ptr]))
//             secNum = nums1[nums1Ptr++];
//         else
//             secNum = nums2[nums2Ptr++];

//         if (++moveCount == mid)
//             return (needNum == 1) ? secNum * 1.0 : (firstNum + secNum) / 2.0;
//     }

//     return -1;
// }

// Version: binary search
int findSmallestK(vector<int> &nums1, int nums1Begin, vector<int> &nums2, int nums2Begin, int k)
{
    int nums1Size = nums1.size(), nums2Size = nums2.size();
    if (nums1Size - nums1Begin > nums2Size - nums2Begin)
        return findSmallestK(nums2, nums2Begin, nums1, nums1Begin, k);
    if (nums1Size == nums1Begin)
        return nums2[nums2Begin + k - 1];
    if (k == 1)
        return min(nums1[nums1Begin], nums2[nums2Begin]);

    int nums1MidIndex = min(int(nums1Size - 1), nums1Begin + k / 2 - 1); //nums1 is small,so it may get to the end of the array
    int nums2MidIndex = nums2Begin + (k - k / 2) - 1;

    if (nums1[nums1MidIndex] < nums2[nums2MidIndex]) // delete k/2 element of nums1 

        return findSmallestK(nums1, nums1MidIndex + 1, nums2, nums2Begin, k - (nums1MidIndex - nums1Begin + 1));
    else
        return findSmallestK(nums1, nums1Begin, nums2, nums2MidIndex + 1, k - (nums2MidIndex - nums2Begin + 1));
}

double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
{
    int totalLength = nums1.size() + nums2.size();
    if (totalLength % 2 == 1)
        return findSmallestK(nums1, 0, nums2, 0, totalLength / 2 + 1);
    else
        return (findSmallestK(nums1, 0, nums2, 0, totalLength / 2) + findSmallestK(nums1, 0, nums2, 0, totalLength / 2 + 1)) / 2.0;
}
