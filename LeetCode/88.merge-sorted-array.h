// 合并两个有序数组

// 难度：简单

// Tags
// array | two-pointers

// 给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。

// 说明:

// 初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
// 你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。

// 示例:

// 输入:
// nums1 = [1,2,3,0,0,0], m = 3
// nums2 = [2,5,6],       n = 3

// 输出: [1,2,2,3,5,6]


#include "parser.h"
#include "debug.h"

void merge(vector<int> &nums1, int m, vector<int> &nums2, int n);

void TestMerge()
{
    vector<int> nums1{1, 4, 7, 8, 0, 0, 0, 0};
    vector<int> nums2{2, 5, 6};
    merge(nums1, 4, nums2, 3);
    DebugVector(nums1);
}

// Version: two pointer
void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
{
    int nums1End = m - 1, nums2End = n - 1, totalEnd = (m + n) - 1;

    while (nums1End >= 0 && nums2End >= 0)
    {
        if (nums2[nums2End] > nums1[nums1End])
            nums1[totalEnd--] = nums2[nums2End--];
        else
            nums1[totalEnd--] = nums1[nums1End--];
    }

    while (nums1End >= 0)
        nums1[totalEnd--] = nums1[nums1End--];
    while (nums2End >= 0)
        nums1[totalEnd--] = nums2[nums2End--];
}
