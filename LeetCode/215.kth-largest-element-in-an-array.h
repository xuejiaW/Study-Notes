// 数组中的第K个最大元素

// 难度：中等

// Tags:
// sorting | stack

// 在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

// 示例 1:

// 输入: [3,2,1,5,6,4] 和 k = 2
// 输出: 5
// 示例 2:

// 输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
// 输出: 4

#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

int findKthLargest(vector<int> &nums, int k);

void TestFindKthLargest()
{
    vector<int> nums{3, 2, 1, 5, 6, 4};
    int result = findKthLargest(nums, 2);
    // vector<int> nums{3, 2, 3, 1, 2, 4, 5, 5, 6};
    // int result = findKthLargest(nums, 4);
    // vector<int> nums{-1, 2, 0};
    // int result = findKthLargest(nums, 2);

    cout << "result is " << result << endl;
}

// // Version: sort
// int findKthLargest(vector<int> &nums, int k)
// {
//     sort(nums.begin(), nums.end(), [](int a, int b) { return a > b; });
//     return nums[k - 1];
// }

// Version: stack
// int findKthLargest(vector<int> &nums, int k)
// {
//     if (nums.empty())
//         return 0;

//     stack<int> mainStack;
//     stack<int> auxiliaryStack;

//     for (const int &i : nums)
//     {
//         int mainSize = mainStack.size();

//         if (mainSize >= k && i <= mainStack.top())
//             continue;
//         while (!mainStack.empty() && i > mainStack.top())
//         {
//             auxiliaryStack.push(mainStack.top());
//             mainStack.pop();
//         }
//         mainStack.push(i);
//         while (!auxiliaryStack.empty())
//         {
//             if (mainSize >= k && auxiliaryStack.size() == 1)
//             {
//                 auxiliaryStack.pop();
//                 continue;
//             }
//             mainStack.push(auxiliaryStack.top());
//             auxiliaryStack.pop();
//         }
//     }
//     return mainStack.top();
// }

// Version: priority_queue
int findKthLargest(vector<int> &nums, int k)
{
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (const int &i : nums)
    {
        minHeap.push(i);
        if (minHeap.size() > k)
            minHeap.pop();
    }
    return minHeap.top();
}
