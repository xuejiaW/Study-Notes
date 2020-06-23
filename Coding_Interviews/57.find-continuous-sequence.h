// 和为s的连续正数序列

// 难度：简单

// Tags:
// two-pointer

// 输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。

// 序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。

// 示例 1：

// 输入：target = 9
// 输出：[[2,3,4],[4,5]]

// 示例 2：

// 输入：target = 15
// 输出：[[1,2,3,4,5],[4,5,6],[7,8]]

#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> findContinuousSequence(int target);

void TestFindContinuousSequence()
{
    vector<vector<int>> result = findContinuousSequence(15);

    for (auto vec : result)
    {
        for (auto i : vec)
            cout << i << " ";
        cout << endl;
    }
}

// Version: two pointer
vector<vector<int>> findContinuousSequence(int target)
{
    vector<vector<int>> result;
    int half = target / 2 + target % 2;

    int left = 1, right = 2;
    int sum = 3;
    while (left <= right && right <= half)
    {
        if (sum == target)
        {
            vector<int> sol;
            for (int i = left; i <= right; ++i)
                sol.push_back(i);
            result.push_back(sol);

            sum += (++right);
        }
        else if (sum < target)
            sum += (++right);
        else if (sum > target)
            sum -= (left++);
    }

    return result;
}