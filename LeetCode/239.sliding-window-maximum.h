// 滑动窗口最大值

// 难度：困难

// 标签:
// sliding-window | heap | deque


// 给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

// 返回滑动窗口中的最大值。

//  

// 进阶：

// 你能在线性时间复杂度内解决此题吗？

// 示例:

// 输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
// 输出: [3,3,5,5,6,7] 
// 解释: 

//   滑动窗口的位置                最大值
// ---------------               -----
// [1  3  -1] -3  5  3  6  7       3
//  1 [3  -1  -3] 5  3  6  7       3
//  1  3 [-1  -3  5] 3  6  7       5
//  1  3  -1 [-3  5  3] 6  7       5
//  1  3  -1  -3 [5  3  6] 7       6
//  1  3  -1  -3  5 [3  6  7]      7

#include <vector>
#include <deque>
#include <iostream>

using namespace std;

vector<int> maxSlidingWindow(vector<int> &nums, int k);

void TestMaxSlidingWidnow()
{
    vector<int> nums{1, 3, -1, -3, 5, 3, 6, 7};

    vector<int> result = maxSlidingWindow(nums, 3);
    for (auto i : result)
        cout << i << " ";
}

// TODO:: Version: using violent

// TODO:: Version: using stack

// Version: using deque O(N)
vector<int> maxSlidingWindow(vector<int> &nums, int k)
{
    vector<int> result;
    int size = nums.size();
    if (size == 0)
        return result;

    deque<int> indexDeque;
    for (int i = 0; i != size; ++i)
    {
        // keep the element is from big to small
        while (!indexDeque.empty() && nums[indexDeque.back()] < nums[i])
            indexDeque.pop_back();

        indexDeque.push_back(i);

        // remove the element outside the window
        while (!indexDeque.empty() && indexDeque.front() <= (i - k))
            indexDeque.pop_front();

        if (i >= (k - 1))
            result.push_back(nums[indexDeque.front()]);
    }

    return result;
}
