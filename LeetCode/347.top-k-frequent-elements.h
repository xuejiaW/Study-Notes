// Tags: 
// hash-table | heap

// Given a non-empty array of integers, return the k most frequent elements.

// Example 1:

// Input: nums = [1,1,1,2,2,3], k = 2
// Output: [1,2]
// Example 2:

// Input: nums = [1], k = 1
// Output: [1]
// Note:

// You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
// Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
// It's guaranteed that the answer is unique, in other words the set of the top k frequent elements is unique.
// You can return the answer in any order.

#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <unordered_map>
#include <map>

using namespace std;

vector<int> topKFrequent(vector<int> &nums, int k);

void TestTopKFrequent()
{
    // vector<int> nums{1, 1, 1, 2, 2, 3};
    // vector<int> nums{-1, -1, -2, -2};
    vector<int> nums{4, 1, -1, 2, -1, 2, 3};
    // vector<int> nums{1};
    int k = 2;

    vector<int> result = topKFrequent(nums, k);
    for (int i : result)
        cout << i << " ";
    cout << endl;
}

// // Version: use unordered_map and map
// vector<int> topKFrequent(vector<int> &nums, int k)
// {
//     unordered_map<int, int> value2TimesMap;
//     map<int, vector<int>> times2ValueMap;
//     vector<int> result;

//     for (const int &i : nums)
//         ++value2TimesMap[i];

//     for (pair<int, int> pair : value2TimesMap)
//         times2ValueMap[pair.second].push_back(pair.first);

//     for (map<int, vector<int>>::reverse_iterator rit = times2ValueMap.rbegin(); rit != times2ValueMap.rend(); ++rit)
//     {
//         result.insert(result.end(), rit->second.begin(), rit->second.end());
//         if (result.size() >= k)
//             break;
//     }

//     return result;
// }

// // Version: use unordered_map and set
// vector<int> topKFrequent(vector<int> &nums, int k)
// {
//     unordered_map<int, int> value2TimeMap;
//     vector<int> result;

//     for (const int &i : nums)
//         ++value2TimeMap[i];

//     set<pair<int, int>> times2ValueSet;

//     for (pair<int, int> pair : value2TimeMap)
//         times2ValueSet.insert({pair.second, pair.first});

//     for (set<pair<int, int>>::reverse_iterator rit = times2ValueSet.rbegin(); rit != times2ValueSet.rend(), k > 0; rit++, k--)
//         result.push_back(rit->second);

//     return result;
// }

// // Version: use priority_queue
vector<int> topKFrequent(vector<int> &nums, int k)
{
    unordered_map<int, int> value2TimeMap;
    vector<int> result;

    for (const int &i : nums)
        ++value2TimeMap[i];

    priority_queue<pair<int, int>> times2ValueMaxHeap;

    int value2TimeMapSize = value2TimeMap.size();
    for (unordered_map<int, int>::iterator it = value2TimeMap.begin(); it != value2TimeMap.end(); ++it)
    {
        times2ValueMaxHeap.push({it->second, it->first});
        if (times2ValueMaxHeap.size() > value2TimeMapSize - k)
        {
            result.push_back(times2ValueMaxHeap.top().second);
            times2ValueMaxHeap.pop();
        }
    }

    return result;
}
