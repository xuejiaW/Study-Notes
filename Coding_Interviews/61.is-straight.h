#include <vector>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

bool isStraight(vector<int> &nums);

void TestIsStraight()
{
    vector<int> nums{0, 0, 8, 5, 4};
    bool result = isStraight(nums);
    cout << "result is " << result << endl;
}

// // Version: whether the joker nums can fill the gap
// bool isStraight(vector<int> &nums)
// {
//     sort(nums.begin(), nums.end());

//     int jokerNums = 0;
//     int gap = 0;
//     for (int i = 0; i != 5; ++i)
//     {
//         if (nums[i] == 0)
//             jokerNums++;
//         else if (i != 0 && nums[i] == nums[i - 1])
//             return false;
//         else if (i != 0 && nums[i - 1] != 0)
//             gap += (nums[i] - nums[i - 1] - 1);
//     }

//     return gap <= jokerNums;
// }

// Version:
// if is straight, then there must be no duplicate cards
// then the (maxValue - minValue) must smaller than 5
bool isStraight(vector<int> &nums)
{
    int maxVal = INT_MIN, minVal = INT_MAX;
    set<int> currCards;
    for (const int &i : nums)
    {
        if (i == 0)
            continue;

        if (currCards.find(i) != currCards.end())
            return false;

        currCards.insert(i);
        maxVal = max(maxVal, i);
        minVal = min(minVal, i);
    }

    return (maxVal - minVal) < 5;
}