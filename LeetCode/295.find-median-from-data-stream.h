// 数据流的中位数

// 难度：困难

// Tags:
// heap | design

// 中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。

// 例如，

// [2,3,4] 的中位数是 3

// [2,3] 的中位数是 (2 + 3) / 2 = 2.5

// 设计一个支持以下两种操作的数据结构：

// void addNum(int num) - 从数据流中添加一个整数到数据结构中。
// double findMedian() - 返回目前所有元素的中位数。

// 示例：
// addNum(1)
// addNum(2)
// findMedian() -> 1.5
// addNum(3) 
// findMedian() -> 2

#include "parser.h"
#include "debug.h"
#include <queue>
#include <algorithm>

// Version: binary search
class MedianFinder
{
public:
    /** initialize your data structure here. */
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        int begin = 0, end = nums.size() - 1, middle = 0, pos = nums.size();
        while (begin <= end)
        {
            middle = (begin + end) / 2;
            if (nums[middle] >= num)
            {
                pos = middle;
                end = middle - 1;
            }
            else
            {
                begin = middle + 1;
            }
        }
        // cout << "lower bound is " << lower_bound(nums.begin(), nums.end(), num) - nums.begin() << endl;
        // cout << "pos is " << pos << endl;

        nums.insert(nums.begin() + pos, num);
    }

    double findMedian()
    {
        int size = nums.size();
        if (size % 2 == 0)
        {
            return (nums[size / 2] + nums[size / 2 - 1]) / 2.0;
        }
        else
        {
            return nums[size / 2];
        }
    }

private:
    vector<int> nums;
};

// Version: two stack
class MedianFinder
{
public:
    /** initialize your data structure here. */
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        if (maxHeap.empty() || num <= maxHeap.top())
            maxHeap.push(num);
        else
            minHeap.push(num);

        if (maxHeap.size() - minHeap.size() == 2)// can not use 1, for maxHeap might be 0, and will be the signed compare to unsigned
        {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        else if (minHeap.size() - maxHeap.size() == 2)
        {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian()
    {
        if (maxHeap.size() > minHeap.size())
            return maxHeap.top();
        else if (maxHeap.size() < minHeap.size())
            return minHeap.top();
        else
            return (maxHeap.top() + minHeap.top()) / 2.0;
    }

private:
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;
};

void TestMedianFinder()
{
    MedianFinder mf = MedianFinder();
    // mf.addNum(-1);
    // mf.addNum(-2);
    // mf.addNum(-3);
    // mf.addNum(-4);
    // mf.addNum(-5);

    mf.addNum(1);
    mf.addNum(4);
    mf.addNum(5);
    mf.addNum(3);
    mf.addNum(6);
    cout << mf.findMedian() << endl;
}
