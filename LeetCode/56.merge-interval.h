// 合并区间

// 难度：中等

// 标签：
// 数组 | 排序

// 给出一个区间的集合，请合并所有重叠的区间。

// 示例 1:

// 输入: [[1,3],[2,6],[8,10],[15,18]]
// 输出: [[1,6],[8,10],[15,18]]
// 解释: 区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].

// 示例 2:

// 输入: [[1,4],[4,5]]
// 输出: [[1,5]]
// 解释: 区间 [1,4] 和 [4,5] 可被视为重叠区间。

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<vector<int>> merge(vector<vector<int>> &intervals);

void TestMerge()
{
    // vector<vector<int>> intervals{
    //     {1, 3}, {2, 6}, {8, 10}, {15, 18}};
    vector<vector<int>> intervals{{1, 3}, {3, 7}, {2, 6}, {8, 10}};

    vector<vector<int>> result = merge(intervals);
    for (auto vec : result)
    {
        for (auto i : vec)
            cout << i << " " << endl;
        cout << endl;
    }
}

// Version: using sort
vector<vector<int>> merge(vector<vector<int>> &intervals)
{
    vector<vector<int>> result;

    int intervalsSize = intervals.size();
    if (intervalsSize == 0)
        return result;

    sort(intervals.begin(), intervals.end());
    result.push_back(intervals[0]);
    for (int i = 1; i != intervalsSize; ++i)
    {
        vector<int> &curr = intervals[i];
        vector<int> &prev = result[result.size() - 1];

        if (curr[0] <= prev[1])
            prev[1] = max(curr[1], prev[1]);
        else
            result.push_back(curr);
    }
    return result;
}
