// 字母异位词分组

// 难度：中等

// Tags: 
// hash-table | string

// 给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。

// 示例:

// 输入: ["eat", "tea", "tan", "ate", "nat", "bat"]
// 输出:
// [
//   ["ate","eat","tea"],
//   ["nat","tan"],
//   ["bat"]
// ]

// 说明：

// 所有输入均为小写字母。
// 不考虑答案输出的顺序。


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
