// 数组中数字出现的次数

// 难度：中等

// Tags：

// maths | bit-opeartion

// 一个整型数组 nums 里除两个数字之外，其他数字都出现了两次。请写程序找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。

//  

// 示例 1：

// 输入：nums = [4,1,4,6]
// 输出：[1,6] 或 [6,1]
// 示例 2：

// 输入：nums = [1,2,10,4,1,4,3,3]
// 输出：[2,10] 或 [10,2]

#include <iostream>
#include <vector>

using namespace std;

vector<int> singleNumbers(vector<int> &nums);

void TestSingleNumbers()
{
    vector<int> nums{1, 2, 10, 4, 1, 4, 3, 3};
    vector<int> result = singleNumbers(nums);
    for (auto i : result)
        cout << i << endl;
}

vector<int> singleNumbers(vector<int> &nums)
{
    // if two numbers are result1 and result2

    // xorResult should equals to result1^result2
    int xorResult = 0;
    for (const int &i : nums)
        xorResult ^= i;

    // find one digit that is 1 in the xorResult
    // this digit in result1 and result 2 must be different
    int digit = 1;
    while ((digit & xorResult) == 0)
        digit <<= 1;

    int result1 = 0, result2 = 0;

    // divide all nums into two group which decided by the gotted result
    // result 1 and result2 must fall into two different group
    // all the same numbers must fall into the same group
    for (const int &i : nums)
    {
        if (digit & i)
            result1 ^= i;
        else
            result2 ^= i;
    }

    return vector<int>{result1, result2};
}