#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std;

int translateNum(int num);

void TestTranslateNum()
{
    int result = translateNum(12258); // 5
    // int result = translateNum(25);
    cout << "result is " << result << endl;
}

// Version: back-tracking
// void translateNum(unordered_map<string, string> &map, unordered_set<string> &resultSet, const string &numStr, string &s, int index);
// int translateNum(int num)
// {
//     unordered_set<string> resultSet;
//     unordered_map<string, string> digit2CharMap;

//     for (int i = 0; i != 26; ++i)
//         digit2CharMap[to_string(i)] = 'a' + i;

//     string numStr = to_string(num);
//     string s = "";
//     translateNum(digit2CharMap, resultSet, numStr, s, 0);

//     return resultSet.size();
// }

// void translateNum(unordered_map<string, string> &digit2Char, unordered_set<string> &resultSet, const string &numStr, string &s, int index)
// {
//     if (index >= numStr.size())
//     {
//         resultSet.insert(s);
//         return;
//     }

//     if (index + 2 <= numStr.size())// if two char is in the map
//     {
//         string temp = numStr.substr(index, 2);
//         if (digit2Char.find(temp) != digit2Char.end())
//         {
//             s += digit2Char[temp];
//             translateNum(digit2Char, resultSet, numStr, s, index + 2);
//             s.erase(s.size() - 1, 1);
//         }
//     }

//     s += digit2Char[numStr.substr(index, 1)];
//     translateNum(digit2Char, resultSet, numStr, s, index + 1);
//     s.erase(s.size() - 1, 1);
// }

// Version: dynamic programming
int translateNum(int num)
{
    string numStr = to_string(num);
    unordered_map<int, int> indexNumMap;

    if (numStr.size() <= 1)
        return 1;

    indexNumMap[0] = 1;
    string sub01 = numStr.substr(0, 2);
    indexNumMap[1] = (sub01 >= "10" && sub01 <= "25") ? 2 : 1;

    for (int i = 2; i != numStr.size(); ++i)
    {
        string sub01 = numStr.substr(i - 1, 2);
        indexNumMap[i] = (sub01 >= "10" && sub01 <= "25") ? indexNumMap[i - 2] + indexNumMap[i - 1] : indexNumMap[i - 1];
    }

    return indexNumMap[numStr.size() - 1];
}
