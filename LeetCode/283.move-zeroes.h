// Tags: 
// array

// Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

// Example:

// Input: [0,1,0,3,12]
// Output: [1,3,12,0,0]
// Note:


#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void moveZeroes(vector<int> &nums);

void TestMoveZeroes()
{
    vector<int> nums{0, 1, 0, 3, 12};
    moveZeroes(nums);
    for (const int &i : nums)
        cout << i << endl;
}

// // Version: with external memory allocation
// void moveZeroes(vector<int> &nums)
// {
//     vector<int> result(nums.size());

//     int index = 0;

//     for (const int &i : nums)
//     {
//         if (i != 0)
//             result[index++] = i;
//     }

//     nums = result;
// }

// Version: without external memory allocation
void moveZeroes(vector<int> &nums)
{
    int zeroNums = 0, numsSize = nums.size();
    for (int i = 0; i != numsSize; ++i)
    {
        if (nums[i] == 0)
            zeroNums++;
        else if (zeroNums != 0)
            nums[i - zeroNums] = nums[i];
    }

    while (zeroNums != 0)
        nums[numsSize - (zeroNums--)] = 0;
}