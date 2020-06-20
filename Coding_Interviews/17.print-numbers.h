
// 打印从1到最大的n位数

// 难度： 简单

// Tags:
// depth-first-search

// 输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999。

// 示例 1:

// 输入: n = 1
// 输出: [1,2,3,4,5,6,7,8,9]
//  

// 说明：

// 用返回一个整数列表来代替打印
// n 为正整数

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

vector<int> printNumbers(int n);

void TestPrintNumbers()
{
    vector<int> result = printNumbers(2);
    for (const int &i : result)
    {
        cout << i << endl;
    }
}

// // Version: not considering bigNums problem
// vector<int> printNumbers(int n)
// {
//     int max = pow(10, n);
//     vector<int> result;
//     for (int i = 1; i != max; ++i)
//         result.push_back(i);
//     return result;
// }

void AddNums(vector<int> &result, string &target, string &curr, int digit, const int &num);

// // Version: considering bigNums problem, DFS
vector<int> printNumbers(int n)
{
    vector<int> result;

    string resultString = "", curr = "";
    AddNums(result, resultString, curr, 0, n);

    // delete last comma
    resultString.erase(resultString.end() - 1);

    // delete first element, it should be sth like 0/00
    int firstComma = resultString.find(',');
    if (firstComma != -1)
        resultString.erase(0, firstComma + 1);

    return result;
}

void AddNums(vector<int> &result, string &target, string &curr, int digit, const int &targetDigit)
{
    if (digit == targetDigit)
    {
        int afterLast0 = 0;

        // delete extra 0, i.e make 0001 to be 1
        if (!curr.empty() && curr[0] == '0')
            afterLast0 = curr.find_first_not_of('0');

        // use const string& to avoid copying
        const string &intValue = (afterLast0 == -1 ? curr : curr.substr(afterLast0, curr.size() - afterLast0));

        // push the number to the result vector
        int value = stoi(intValue);
        if (value != 0)
        {
            result.push_back(value);
        }

        target += intValue + ",";

        if (*(curr.end() - 1) == '9')
        {
            // e.g. make 1899 to be 1
            int lastNot9 = curr.find_last_not_of("9");
            curr.erase(lastNot9 != -1 ? lastNot9 : 0);
        }
        else
        {
            // e.g. make 1898 to be 189
            curr.erase(curr.end() - 1);
        }

        return;
    }

    for (int i = 0; i <= 9; i++)
    {
        curr += to_string(i);
        AddNums(result, target, curr, digit + 1, targetDigit);
    }
}