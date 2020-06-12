#pragma once

// Tags:
// array | hash-table

// Given an array of integers, return indices of the two numbers such that they add up to a specific target.

// You may assume that each input would have exactly one solution, and you may not use the same element twice.

// Example:

// Given nums = [2, 7, 11, 15], target = 9,

// Because nums[0] + nums[1] = 2 + 7 = 9,
// return [0, 1].

#include <iostream>
#include <vector>
#include <map>
#include <iterator>

using namespace std;

vector<int> twoSum(vector<int> &nums, int target);

void TestTwoSum()
{
    // vector<int> nums{2, 7, 11, 15};
    // int target = 9;

    // vector<int> nums{3, 2, 4};
    // int target = 6;

    // vector<int> nums{3, 3};
    // int target = 6;

    // vector<int> nums{0, 4, 3, 0};
    // int target = 0;

    vector<int> nums{6, 4, 3, 0};
    int target = 6;

    vector<int> result = twoSum(nums, target);

    for (int i : result)
        cout << i << " " << endl;
}

vector<int> twoSum(vector<int> &nums, int target)
{
    map<int, int> valueIndexDict;
    for (int i = 0; i < nums.size(); i++)
    {
        if (valueIndexDict.find(target - nums[i]) != valueIndexDict.end())
            return vector<int>{valueIndexDict[target - nums[i]], i};
        valueIndexDict[nums[i]] = i;
    }

    return vector<int>();
}