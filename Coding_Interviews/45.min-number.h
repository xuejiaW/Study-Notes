#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string minNumber(vector<int> &nums);

void TestMinNumber()
{
    vector<int> nums{3, 30, 34, 5, 9};
    string result = minNumber(nums);
    cout << "result is " << result << endl;
}


// Version: sorting
// if a = 3, b = 30 and 303 < 330, so b < a
string minNumber(vector<int> &nums)
{
    vector<string> numsStr;
    for (auto i : nums)
        numsStr.push_back(to_string(i));

    sort(numsStr.begin(), numsStr.end(), [](string a, string b) { return stoll(a + b) < stoll(b + a); });

    string result;
    for (auto s : numsStr)
        result += s;

    if (!result.empty() && result[0] == 0)
    {
        int index = result.find_first_not_of('0');
        if (index != -1)
            result = result.erase(0, index + 1);
        else
            return "0";
    }

    return result;
}