// Tags:
// array | hash-table
// Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

// Example 1:

// Input:nums = [1,1,1], k = 2
// Output: 2
 

// Constraints:

// The length of the array is in range [1, 20,000].
// The range of numbers in the array is [-1000, 1000] and the range of the integer k is [-1e7, 1e7].


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
// int subarraySum(vector<int> &nums, int k)
// {
//     int result = 0, vecSize = nums.size(), sum = 0;

//     unordered_map<int, vector<int>> sum2IndexMap;
//     vector<int> sumVec;

//     sum2IndexMap[0].push_back(-1);

//     for (int i = 0; i < vecSize; i++)
//     {
//         sum += nums[i];
//         sum2IndexMap[sum].push_back(i);
//         sumVec.push_back(sum);
//     }

//     vecSize = sumVec.size();
//     int targetValue = 0;
//     for (int i = 0; i != vecSize; ++i)
//     {
//         targetValue = sumVec[i] - k;
//         if (sum2IndexMap.find(targetValue) != sum2IndexMap.end())
//         {
//             vector<int> &indexes = sum2IndexMap[targetValue];
//             result += count_if(indexes.begin(), indexes.end(), [i](int index) { return index < i; });
//         }
//     }

//     return result;
// }

// // Version: calculating while summing
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
