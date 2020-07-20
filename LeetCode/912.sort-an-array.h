// 912. 排序数组

// 难度：中等

// Tags:
// Sorting

// 给你一个整数数组 nums，请你将该数组升序排列。

// 示例 1：

// 输入：nums = [5,2,3,1]
// 输出：[1,2,3,5]
// 示例 2：

// 输入：nums = [5,1,1,2,0,0]
// 输出：[0,0,1,1,2,5]

#include "parser.h"
#include "debug.h"

vector<int> sortArray(vector<int> &nums);
void TestSortArray()
{
    // vector<int> nums{5, 2, 3, 1};
    vector<int> nums{39, 31, 26, 5, 10, 14, 19, 27};

    vector<int> result = sortArray(nums);
    cout << endl;
    DebugVector(result);
}

void quickSort(vector<int> &nums, int left, int right);
void HeapSort(vector<int> &nums);
void MergeSort(vector<int> &nums, vector<int> &temp, int left, int right);
void CountingSort(vector<int> &nums);

vector<int> sortArray(vector<int> &nums)
{
    // quickSort(nums, 0, nums.size() - 1);
    // HeapSort(nums);

    // vector<int> temp(nums.size(), 0);
    // MergeSort(nums, temp, 0, nums.size() - 1);

    CountingSort(nums);
    return nums;
}

// // Version: quick sort
// void quickSort(vector<int> &nums, int left, int right)
// {
//     if (left >= right)
//         return;
//     swap(nums[right], nums[left + rand() % (right - left + 1)]); // randomly select a element as the reference element

//     int i = left, j = right, ref = nums[right];
//     while (i < j)
//     {
//         while (i < j && nums[i] <= ref)
//             ++i;
//         nums[j] = nums[i];
//         while (i < j && nums[j] >= ref)
//             --j;
//         nums[i] = nums[j];
//     }
//     nums[i] = ref;

//     quickSort(nums, left, i - 1);
//     quickSort(nums, i + 1, right);
// }

// // Version: heap sort
// void maxHeapify(vector<int> &nums, int head, const int heapSize);
// void HeapSort(vector<int> &nums)
// {
//     int lastIndex = nums.size() - 1;

//     for (int i = lastIndex / 2; i >= 0; --i) // build max heap from bottom to top
//         maxHeapify(nums, i, lastIndex);

//     for (int i = lastIndex; i != 0; --i)
//     {
//         swap(nums[i], nums[0]); //make the largest to the last of the array and maintain the maxHeap
//         maxHeapify(nums, 0, --lastIndex);
//     }
// }

// void maxHeapify(vector<int> &nums, int head, const int lastIndex)
// {
//     if (head > lastIndex)
//         return;

//     // find largest element between head,leftChild,rightChild
//     int largest = head, leftNode = head * 2 + 1, rightNode = head * 2 + 2;

//     if (leftNode <= lastIndex && nums[leftNode] > nums[largest])
//         largest = leftNode;
//     if (rightNode <= lastIndex && nums[rightNode] > nums[largest])
//         largest = rightNode;

//     if (largest != head)
//     {
//         swap(nums[largest], nums[head]);
//         maxHeapify(nums, largest, lastIndex);
//     }
// }

// // Version: merge sort
// void MergeSort(vector<int> &nums, vector<int> &temp, int left, int right)
// {
//     if (left >= right)
//         return;

//     int middle = (left + right) / 2;
//     // sort left and right part
//     MergeSort(nums, temp, left, middle);
//     MergeSort(nums, temp, middle + 1, right);

//     // Merge
//     int leftBegin = left, rightBegin = middle + 1, toInsert = 0;
//     while (leftBegin <= middle && rightBegin <= right)
//         temp[toInsert++] = nums[leftBegin] < nums[rightBegin] ? nums[leftBegin++] : nums[rightBegin++];
//     while (leftBegin <= middle)
//         temp[toInsert++] = nums[leftBegin++];
//     while (rightBegin <= right)
//         temp[toInsert++] = nums[rightBegin++];

//     for (int i = 0; i != right - left + 1; ++i)
//         nums[left + i] = temp[i];
// }

// Version: counting sort
void CountingSort(vector<int> &nums)
{
    int minVal = INT_MAX, maxVal = INT_MIN;
    for (const int &i : nums)
    {
        minVal = min(i, minVal);
        maxVal = max(i, maxVal);
    }

    vector<int> counter(maxVal - minVal + 1);
    for (const int &i : nums)
    {
        counter[i - minVal]++;
    }

    int toInsertIndex = 0;
    for (int i = 0; i != counter.size(); ++i)
    {
        while (counter[i] != 0 && toInsertIndex < nums.size())
        {
            nums[toInsertIndex++] = minVal + i;
            counter[i]--;
        }
    }
}
