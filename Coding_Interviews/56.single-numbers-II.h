// 数组中数字出现的次数 II

// 难度：中等

// Tags:
// math | bit-operation

// 在一个数组 nums 中除一个数字只出现一次之外，其他数字都出现了三次。请找出那个只出现一次的数字。

// 示例 1：

// 输入：nums = [3,4,3,3]
// 输出：4

// 示例 2：

// 输入：nums = [9,1,7,9,7,9,7]
// 输出：1

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int singleNumbers(vector<int> &nums);

void TestSingleNumbers()
{
    vector<int> nums{9, 6, 7, 9, 7, 9, 7};
    int result = singleNumbers(nums);
    cout << "result is " << result << endl;
}

// // Version: hash map
// int singleNumbers(vector<int> &nums)
// {
//     unordered_map<int, int> num2TimesMap;
//     for (const int &i : nums)
//         num2TimesMap[i]++;

//     for (const int &i : nums)
//     {
//         if (num2TimesMap[i] == 1)
//             return i;
//     }
//     return 0;
// }

// Version: bit-operation
int singleNumbers(vector<int> &nums)
{
    int result = 0;

    // calculating the count for every digit
    // if any word appears three times, the count % 3 must be 0
    for (int i = 0; i != 32; ++i)
    {
        int count = 0;
        int target = 1 << i;

        for (const int &val : nums)
        {
            if (val & target)
                count++;
        }

        // use the digit to get the result
        if (count % 3 == 1)
            result |= target;
    }

    return result;
}