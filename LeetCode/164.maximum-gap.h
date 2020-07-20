// 最大间距

// 难度：困难

// Tags: sorting

// 给定一个无序的数组，找出数组在排序之后，相邻元素之间最大的差值。

// 如果数组元素个数小于 2，则返回 0。

// 示例 1:

// 输入: [3,6,9,1]
// 输出: 3
// 解释: 排序后的数组是 [1,3,6,9], 其中相邻元素 (3,6) 和 (6,9) 之间都存在最大差值 3。
// 示例 2:

// 输入: [10]
// 输出: 0
// 解释: 数组元素个数小于 2，因此返回 0。

#include "debug.h"
#include "parser.h"

class Bucket
{
public:
    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    bool used = false;
};

int maximumGap(vector<int> &nums);

void TestMaximumGap()
{
    vector<int> nums{3, 6, 9, 1};
    cout << maximumGap(nums);
}
int maximumGap(vector<int> &nums)
{
    if (nums.size() < 2)
        return 0;
    int minVal = INT_MAX, maxVal = INT_MIN;

    for (int i = 0; i != nums.size(); ++i)
    {
        minVal = min(nums[i], minVal);
        maxVal = max(nums[i], maxVal);
    }

    // bucketsNum = gapNum + 1
    int bucketSize = max(1, (maxVal - minVal) / ((int)nums.size() - 1)); // to gap num,so minus 1
    int bucketNum = (maxVal - minVal) / bucketSize + 1;                  // to bucketNum so add 1
    vector<Bucket> buckets(bucketNum);

    for (int i = 0; i != nums.size(); ++i)
    {
        int index = (nums[i] - minVal) / bucketSize;
        buckets[index].used = true;
        buckets[index].minVal = min(nums[i], buckets[index].minVal);
        buckets[index].maxVal = max(nums[i], buckets[index].maxVal);
    }

    int prevBucketMax = minVal, maxGap = 0;
    for (int i = 0; i != buckets.size(); ++i)
    {
        if (!buckets[i].used)
            continue;
        maxGap = max(maxGap, buckets[i].minVal - prevBucketMax);
        prevBucketMax = buckets[i].maxVal;
    }
    return maxGap;
}
