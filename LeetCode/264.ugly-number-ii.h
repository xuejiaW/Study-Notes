// 丑数 II

// 难度：中等

// 编写一个程序，找出第 n 个丑数。

// 丑数就是质因数只包含 2, 3, 5 的正整数。

// 示例:

// 输入: n = 10
// 输出: 12
// 解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
// 说明:  

// 1 是丑数。
// n 不超过1690

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int nthUglyNumber(int n);

void TestnthUglyNumber()
{
    int result = nthUglyNumber(10);
    cout << "result is " << result << endl;
}

int nthUglyNumber(int n)
{
    vector<int> unlyNumVec;
    int twoPointer = 0, threePointer = 0, fivePointer = 0;

    unlyNumVec.push_back(1);
    while (unlyNumVec.size() < n)
    {
        int two = unlyNumVec[twoPointer] * 2, three = unlyNumVec[threePointer] * 3,
            five = unlyNumVec[fivePointer] * 5;

        int minValue = min(two, min(three, five));

        if (minValue == two)
            twoPointer++;
        if (minValue == three)
            threePointer++;
        if (minValue == five)
            fivePointer++;
        unlyNumVec.push_back(minValue);
    }

    return unlyNumVec[n - 1];
}
