// Tags:
// hash-table | bit-manipulation

// Given a non-empty array of integers, every element appears twice except for one. Find that single one.

// Note:

// Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

// Example 1:

// Input: [2,2,1]
// Output: 1

// Example 2:

// Input: [4,1,2,1,2]
// Output: 4

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;
int singleNumber(vector<int> &nums);

void TestSingleNumber()
{
    // vector<int> iVec = {2, 2, 1};
    vector<int> iVec = {4, 1, 2, 1, 2};

    int result = singleNumber(iVec);

    cout << result << endl;
}

//// Version: Use extra memory
int singleNumber(vector<int> &nums)
{
    unordered_map<int, int> valueTimesDict;

    for (int i : nums)
        valueTimesDict[i]++;

    for (unordered_map<int, int>::iterator i = valueTimesDict.begin(); i != valueTimesDict.end(); ++i)
        if (i->second == 1)
            return i->first;

    return 0;
}


// Version: Use xor (bit-manipulation) 
// Property of xor: if a xor b twice, the result is still a
// e.g. a xor b = c --> c xor b =a
int singleNumber(vector<int> &nums)
{
    int result = nums[0];
    for (int i = 1; i != nums.size(); ++i)
        result = result ^ nums[i];
    return result;
}
