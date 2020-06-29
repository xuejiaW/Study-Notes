// 和为K的子数组

// 难度：中等

// 标签：
// 数组 | 哈希表

// 给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。

// 示例 1 :

// 输入:nums = [1,1,1], k = 2
// 输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。
// 说明 :

// 数组的长度为 [1, 20,000]。
// 数组中元素的范围是 [-1000, 1000] ，且整数 k 的范围是 [-1e7, 1e7]



#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int subarraySum(vector<int> &nums, int k);

void TestSubarraySum()
{
    // vector<int> nums{1, 1, 1};
    // int k = 2;

    // vector<int> nums{1, 5, 2, -4, 2, 2, 0, -4, 4};
    // int k = 4;

    // vector<int> nums{1};
    // int k = 0;

    // vector<int> nums{1, 2, 1, 2, -2, 4};
    // int k = 4;

    vector<int> nums{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int k = 0;

    int result = subarraySum(nums, k);
    cout << "result is " << result << endl;
}

// Version: first calculating all the sum result
int subarraySum(vector<int> &nums, int k)
{
    int result = 0, vecSize = nums.size(), sum = 0;

    unordered_map<int, vector<int>> sum2IndexMap;
    vector<int> sumVec;

    sum2IndexMap[0].push_back(-1);

    for (int i = 0; i < vecSize; i++)
    {
        sum += nums[i];
        sum2IndexMap[sum].push_back(i);
        sumVec.push_back(sum);
    }

    vecSize = sumVec.size();
    int targetValue = 0;
    for (int i = 0; i != vecSize; ++i)
    {
        targetValue = sumVec[i] - k;
        if (sum2IndexMap.find(targetValue) != sum2IndexMap.end())
        {
            vector<int> &indexes = sum2IndexMap[targetValue];
            result += count_if(indexes.begin(), indexes.end(), [i](int index) { return index < i; });
        }
    }

    return result;
}

// Version: calculating while summing
int subarraySum(vector<int> &nums, int k)
{
    int result = 0, sum = 0;
    unordered_map<int, int> sum2TimeMap{{0, 1}};

    for (const int &i : nums)
    {
        sum += i;
        result += sum2TimeMap[sum - k];
        sum2TimeMap[sum]++;
    }

    return result;
}
