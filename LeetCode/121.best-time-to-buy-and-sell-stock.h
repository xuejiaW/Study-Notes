#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int maxProfit(vector<int> &prices);

void TestMaxProfit()
{
    // vector<int> prices{7, 1, 5, 3, 6, 4};
    // vector<int> prices{7, 6, 4, 3, 1};
    vector<int> prices{0, 1};
    int result = maxProfit(prices);
    cout << "result is " << result << endl;
}

int maxProfit(vector<int> &prices)
{
    int maxProfit = 0, minPrice = INT_MAX, currProfit = 0;

    for (const int &p : prices)
    {
        currProfit = p - minPrice;
        maxProfit = max(maxProfit, currProfit);
        minPrice = min(minPrice, p);
    }

    return maxProfit;
}
