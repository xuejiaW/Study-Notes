// 调整数组顺序使奇数位于偶数前面

// 难度：简单

// Tags:

// two-pointer

// 输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数位于数组的前半部分，所有偶数位于数组的后半部分。

//  

// 示例：

// 输入：nums = [1,2,3,4]
// 输出：[1,3,2,4] 
// 注：[3,1,2,4] 也是正确的答案之一。

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> exchange(vector<int> &nums);

void TestExchange()
{
    vector<int> nums{2};

    vector<int> result = exchange(nums);
    for (const int &i : result)
        cout << i << endl;
}

vector<int> exchange(vector<int> &nums)
{
    vector<int> result = nums;
    int evenPointer = 0, oddPointer = result.size() - 1;

    while (evenPointer < oddPointer)
    {
        while (result[evenPointer] % 2 == 1 && evenPointer < oddPointer)
            ++evenPointer;
        while (result[oddPointer] % 2 == 0 && evenPointer < oddPointer)
            --oddPointer;

        swap(result[evenPointer++], result[oddPointer--]);
    }

    return result;
}