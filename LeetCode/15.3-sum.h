// 三数之和

// 难度：中等

// Tags
// array | two-pointers

// 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。

// 注意：答案中不可以包含重复的三元组。

//  

// 示例：

// 给定数组 nums = [-1, 0, 1, 2, -1, -4]，

// 满足要求的三元组集合为：
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
        // reduce duplicate answer
        while (i + 1 < numsSize && nums[i] == nums[i + 1])
            ++i;
    }

    return result;
}
