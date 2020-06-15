// Tags: 
// hash-table | string

// Given an array of strings, group anagrams together.

// Example:

// Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
// Output:
// [
//   ["ate","eat","tea"],
//   ["nat","tan"],
//   ["bat"]
// ]
// Note:

// All inputs will be in lowercase.
// The order of your output does not matter.

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<vector<string>> groupAnagrams(vector<string> &strs);

void TestGroupAnagrams()
{
    vector<string> sVec = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<vector<string>> result = groupAnagrams(sVec);
    for (vector<string> &vec : result)
    {
        for (string &str : vec)
        {
            cout << str << " " << endl;
        }
        cout << endl;
    }
}

vector<vector<string>> groupAnagrams(vector<string> &strs)
{
    vector<vector<string>> result;

    unordered_map<string, int> anagrams2IndexMap;

    vector<string> orderedStrs(strs.begin(), strs.end());
    for (string &s : orderedStrs)
        sort(s.begin(), s.end());

    int strsSize = strs.size();

    for (int i = 0; i != strsSize; ++i)
    {
        if (anagrams2IndexMap.find(orderedStrs[i]) == anagrams2IndexMap.end())
        {
            result.push_back(vector<string>{strs[i]});
            anagrams2IndexMap[orderedStrs[i]] = result.size() - 1;
        }
        else
        {
            result[anagrams2IndexMap[orderedStrs[i]]].push_back(strs[i]);
        }
    }
    return result;
}
