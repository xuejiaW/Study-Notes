// Tags
// array | two-pointers

// Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

// Note:

// The solution set must not contain duplicate triplets.

// Example:

// Given array nums = [-1, 0, 1, 2, -1, -4],

// A solution set is:
// [
//   [-1, 0, 1],
//   [-1, -1, 2]
// ]

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<vector<int>> threeSum(vector<int> &nums);

void Test3Sum()
{
    vector<int> nums{-1, 0, 1, 2, -1, -4};
    vector<vector<int>> result = threeSum(nums);
    for (vector<int> vec : result)
    {
        for (int i : vec)
        {
            cout << i << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> threeSum(vector<int> &nums)
{
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());

    int numsSize = nums.size();

    for (int i = 0; i != numsSize; ++i)
    {
        int j = i + 1, k = numsSize - 1;
        while (j < k)
        {
            int curr = nums[i] + nums[j] + nums[k];
            if (curr < 0)
                j++;
            else if (curr > 0)
                k--;
            else //curr == target
            {
                vector<int> toInsert{nums[i], nums[j], nums[k]};
                result.push_back(toInsert);
                //reduce duplicate answer
                while (j < k && nums[j] == toInsert[1])
                    ++j;
                while (j < k && nums[k] == toInsert[2])
                    --k;
            }
        }
        while (i + 1 < numsSize && nums[i] == nums[i + 1])
            ++i;
    }

    return result;
}
