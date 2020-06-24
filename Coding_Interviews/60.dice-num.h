// // n个骰子的点数

// 把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s的所有可能的值出现的概率。

// 示例 1:

// 输入: 1
// 输出: [0.16667,0.16667,0.16667,0.16667,0.16667,0.16667]
// 示例 2:

// 输入: 2
// 输出: [0.02778,0.05556,0.08333,0.11111,0.13889,0.16667,0.13889,0.11111,0.08333,0.05556,0.02778]

#include <vector>
#include <iostream>

using namespace std;

vector<double> diceNum(int n);

void TestDiceNum()
{
    vector<double> result = diceNum(2);
    for (auto val : result)
        cout << val << endl;
}

// Version: dynamic programming
vector<double> diceNum(int n)
{
    vector<vector<double>> probabities;
    probabities.push_back({0, 0, 0, 0, 0, 0}); // zero dices
    probabities.push_back({1, 1, 1, 1, 1, 1});

    for (int diceNums = 2; diceNums <= n; ++diceNums) // nums of dices
    {
        probabities.push_back(vector<double>(diceNums * 6 - diceNums + 1));
        for (int sum = diceNums; sum <= diceNums * 6; ++sum) // num
        {
            probabities[diceNums][sum - diceNums] = 0;
            for (int curr = 1; curr <= 6; ++curr) // current dice num
            {
                if ((sum - curr) >= (diceNums - 1) && (sum - curr) <= 6 * (diceNums - 1))
                {
                    // the probabilities in the situation when the dices nums small by 1
                    probabities[diceNums][sum - diceNums] += probabities[diceNums - 1][sum - (diceNums - 1) - curr];
                }
            }
        }
    }

    for (double &d : probabities[n])
        d *= pow(1 / 6.0, n); // plus the possibility 1/6

    return probabities[n];
}