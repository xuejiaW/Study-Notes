// 两数之和 III - 数据结构设计

// 难度：简单

// Tags：
// design | hashmap | sorting

// 设计并实现一个 TwoSum 的类，使该类需要支持 add 和 find 的操作。

// add 操作 -  对内部数据结构增加一个数。
// find 操作 - 寻找内部数据结构中是否存在一对整数，使得两数之和与给定的数相等。

// 示例 1:
// add(1); add(3); add(5);
// find(4) -> true
// find(7) -> false

// 示例 2:
// add(3); add(1); add(2);
// find(3) -> true
// find(6) -> false

#include "parser.h"
#include "debug.h"
#include <unordered_map>

// Version: hash_map
// class TwoSum
// {
// public:
//     TwoSum() {}

//     void add(int number)
//     {
//         valArr.push_back(number);
//         if (value2FirstExistIndexMap.find(number) == value2FirstExistIndexMap.end())
//             value2FirstExistIndexMap.insert({number, valArr.size() - 1});
//     }

//     bool find(int value)
//     {
//         for (int i = 0; i != valArr.size(); ++i)
//         {
//             int toFind = value - valArr[i];
//             if (value2FirstExistIndexMap.find(toFind) != value2FirstExistIndexMap.end() && value2FirstExistIndexMap[toFind] != i)
//                 return true;
//         }
//         return false;
//     }

// private:
//     vector<int> valArr;
//     unordered_map<int, int> value2FirstExistIndexMap;
// };

// Version: using insert sorting to maintain vector ordered
class TwoSum
{
public:
    /** Initialize your data structure here. */
    TwoSum()
    {
    }

    /** Add the number to an internal data structure.. */
    void add(int number)
    {
        int valArrSize = valArr.size();
        if (valArrSize == 0)
            valArr.push_back(number);
        else
        {
            int left = 0, right = valArrSize - 1, toInsert = valArrSize;
            while (left <= right)
            {
                int middle = (left + right) / 2;
                if (valArr[middle] > number)
                {
                    toInsert = middle;
                    right = middle - 1;
                }
                else
                {
                    left = middle + 1;
                }
            }

            valArr.insert(valArr.begin() + toInsert, number);
        }
    }

    /** Find if there exists any pair of numbers which sum is equal to the value. */
    bool find(int value)
    {
        int valArrSize = valArr.size();
        if (valArrSize < 2)
            return false;
        int left = 0, right = valArrSize - 1;
        while (left < right)
        {
            int sum = valArr[left] + valArr[right];
            if (sum == value)
                return true;
            else if (sum > value)
                right--;
            else if (sum < value)
                left++;
        }
        return false;
    }

private:
    vector<int> valArr;
};

void TestTwoSum()
{
    TwoSum twoSum;
    twoSum.add(1);
    twoSum.add(2);
    twoSum.add(3);
    cout << twoSum.find(5) << endl;
    cout << twoSum.find(7) << endl;
}
