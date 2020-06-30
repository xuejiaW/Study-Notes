// 零钱兑换

// 难度：中等

// Tags:
// dynamic programming

// 给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。

// 示例 1:

// 输入: coins = [1, 2, 5], amount = 11
// 输出: 3
// 解释: 11 = 5 + 5 + 1

// 示例 2:

// 输入: coins = [2], amount = 3
// 输出: -1

#include "parser.h"
#include "debug.h"
#include <algorithm>
#include <unordered_map>

int coinChange(vector<int> &coins, int amount);

void TestCoinChange()
{
    vector<int> coins{1, 3, 5};
    int result = coinChange(coins, 11);
    cout << result << endl;
}

// // Version: dynamic programming, find the solution
// int coinChange(vector<int> &coins, int amount)
// {
//     if (amount == 0)
//         return 0;
//     sort(coins.begin(), coins.end(), [](int a, int b) { return a > b; });

//     unordered_map<int, vector<int>> amount2SolutionsMap;
//     for (int i = 1; i <= amount; ++i)
//     {
//         int minSize = INT_MAX;
//         for (const int &coin : coins)
//         {
//             int target = i - coin;
//             if (target < 0)
//                 continue;

//             if (target == 0)
//             {
//                 amount2SolutionsMap[i].push_back({coin});
//                 minSize = 1;
//             }
//             else if (amount2SolutionsMap.find(target) != amount2SolutionsMap.end())
//             {
//                 vector<int> targetSol = amount2SolutionsMap[target];
//                 if (targetSol.size() + 1 < minSize)
//                 {
//                     minSize = targetSol.size() + 1;
//                     targetSol.push_back(coin);
//                     amount2SolutionsMap[i] = targetSol;
//                 }
//             }
//         }
//     }

//     if (amount2SolutionsMap.find(amount) == amount2SolutionsMap.end())
//         return -1;

//     return amount2SolutionsMap[amount].size();
// }

// Version: dynamic programming, only coins
int coinChange(vector<int> &coins, int amount)
{
    if (amount == 0)
        return 0;

    vector<int> amount2NumsMap(amount + 1, -1);
    for (int i = 1; i <= amount; ++i)
    {
        int minSize = INT_MAX;
        for (const int &coin : coins)
        {
            int target = i - coin;
            if (target < 0)
                continue;

            if (target == 0)
            {
                amount2NumsMap[i] = 1;
                minSize = 1;
            }
            else if (amount2NumsMap[target] != -1)
            {
                int nums = amount2NumsMap[target];
                if (nums + 1 < minSize)
                {
                    minSize = nums + 1;
                    amount2NumsMap[i] = minSize;
                }
            }
        }
    }
    return amount2NumsMap[amount];
}
