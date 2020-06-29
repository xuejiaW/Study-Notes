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
    if (intervals.empty())
        return vector<vector<int>>();

    sort(intervals.begin(), intervals.end());

    vector<vector<int>> result;
    vector<int> solution = intervals[0];

    for (int i = 1; i != intervals.size(); ++i)
    {
        if (intervals[i][0] <= solution[1])
        {
            solution[1] = max(intervals[i][1], solution[1]);
        }
        else
        {
            result.push_back(solution);
            solution = intervals[i];
        }
    }
    result.push_back(solution);

    return result;
}

// vector<vector<int>> merge(vector<vector<int>> &intervals)
// {
// }
