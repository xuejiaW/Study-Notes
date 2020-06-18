// Tags
// recursive | dynamic-programmming

// The Fibonacci numbers, commonly denoted F(n) form a sequence, called the Fibonacci sequence, such that each number is the sum of the two preceding ones, starting from 0 and 1. That is,

// F(0) = 0,   F(1) = 1
// F(N) = F(N - 1) + F(N - 2), for N > 1.
// Given N, calculate F(N).

#include <vector>
#include <iostream>
using namespace std;

int fib(int N);

void TestFib()
{
    int result = fib(0);
    cout << "result is " << result << endl;
}

// //Version: Recursive
// int fib(int N)
// {
//     if (N == 0 || N == 1)
//         return N;
//     else
//         return fib(N - 1) + fib(N - 2);
// }

//Version: dynamic programming
int fib(int N)
{
    if (N == 0)
        return 0;

    vector<int> dp(N + 1);
    dp[1] = 1;

    for (int i = 2; i <= N; ++i)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[N];
}
