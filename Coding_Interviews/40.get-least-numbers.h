// 最小的k个数

// 难度：简单

// Tags:
// heap

// 输入整数数组 arr ，找出其中最小的 k 个数。例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。

//  

// 示例 1：

// 输入：arr = [3,2,1], k = 2
// 输出：[1,2] 或者 [2,1]
// 示例 2：

// 输入：arr = [0,1,2,1], k = 1
// 输出：[0]

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> getLeastNumbers(vector<int> &arr, int k);

void TestGetLeastNumbers()
{
    // vector<int> nums{3, 2, 1};
    // int target = 1;

    vector<int> nums{1, 3, 2, 1};
    int target = 2;

    vector<int> result = getLeastNumbers(nums, target);

    for (int i : result)
        cout << i << " " << endl;
}

// Version: using sort
// vector<int> getLeastNumbers(vector<int> &arr, int k)
// {
//     sort(arr.begin(), arr.end());

//     vector<int> result;
//     for (int i = 0; i != k; ++i)
//         result.push_back(arr[i]);

//     return result;
// }

// Version: using heap
vector<int> getLeastNumbers(vector<int> &arr, int k)
{
    vector<int> result;
    if (k == 0)
        return result;
    priority_queue<int> maxQueue;

    for (int i = 0; i != k; ++i)
        maxQueue.push(arr[i]);

    for (int i = k; i != arr.size(); ++i)
    {
        if (arr[i] < maxQueue.top())
        {
            maxQueue.pop();
            maxQueue.push(arr[i]);
        }
    }

    for (int i = 0; i != k; ++i)
    {
        result.push_back(maxQueue.top());
        maxQueue.pop();
    }

    return result;
}

// Version: method like quick sort
// https: //leetcode-cn.com/problems/zui-xiao-de-kge-shu-lcof/solution/zui-xiao-de-kge-shu-by-leetcode-solution/
