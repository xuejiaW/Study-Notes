// Tags:
// hash-table | stack

// Given a list of daily temperatures T, return a list such that, for each day in the input, tells you how many days you would have to wait until a warmer temperature. If there is no future day for which this is possible, put 0 instead.

// For example, given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73], your output should be [1, 1, 4, 2, 1, 1, 0, 0].

// Note: The length of temperatures will be in the range [1, 30000]. Each temperature will be an integer in the range [30, 100].

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

vector<int> dailyTemperatures(vector<int> &T);

void TestDailyTemperature()
{
    vector<int> t{73, 74, 75, 71, 69, 72, 76, 73};
    // vector<int> t{0};

    vector<int> result = dailyTemperatures(t);
    cout << "result num is " << result.size() << endl;
    for (const int &i : result)
        cout << i << endl;
}

// // Version: brutal solution
// vector<int> dailyTemperatures(vector<int> &T)
// {
//     vector<int> result;
//     int tSizeMinus1 = T.size();

//     bool found = false;
//     for (int i = 0; i != tSizeMinus1; ++i)
//     {
//         found = false;
//         for (int j = i + 1; j != tSizeMinus1; ++j)
//         {
//             if (T[j] > T[i])
//             {
//                 result.push_back(j - i);
//                 found = true;
//                 break;
//             }
//         }
//         if (!found)
//             result.push_back(0);
//     }

//     return result;
// }

// Version: using find_if algorithm
// vector<int> dailyTemperatures(vector<int> &T)
// {
//     vector<int> result;
//     vector<int>::iterator currIt = T.begin();
//     vector<int>::iterator resultIT;
//     for (currIt; currIt != T.end(); ++currIt)
//     {
//         resultIT = find_if(currIt, T.end(), [currIt](int value) { return value > (*currIt); });
//         if (resultIT != T.end())
//             result.push_back(resultIT - currIt);
//         else
//             result.push_back(0);
//     }
//     return result;
// }

// Version: use priority queue
// vector<int> dailyTemperatures(vector<int> &T)
// {
//     int tsize = T.size();
//     vector<int> result(tsize, 0);
//     priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> waitingRaiseValueQueue;

//     pair<int, int> topValue;
//     for (int i = 0; i != tsize; ++i)
//     {
//         while (waitingRaiseValueQueue.size() != 0)
//         {
//             topValue = waitingRaiseValueQueue.top();
//             if (topValue.first < T[i])
//             {
//                 result[topValue.second] = i - topValue.second;
//                 waitingRaiseValueQueue.pop();
//             }
//             else
//             {
//                 break;
//             }
//         }
//         waitingRaiseValueQueue.push({T[i], i});
//     }
//     return result;
// }

// Version：using stack
vector<int> dailyTemperatures(vector<int> &T)
{
    vector<int> result = vector<int>(T.size());

    stack<int> indexStack;
    indexStack.push(0);

    for (int i = 1; i != T.size(); ++i)
    {
        while (!indexStack.empty() && T[i] > T[indexStack.top()]) //Keep the stack is descending
        {
            result[indexStack.top()] = i - indexStack.top();
            indexStack.pop();
        }
        indexStack.push(i);
    }
    return result;
}
