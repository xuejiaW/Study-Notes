#include "parser.h"
#include "debug.h"

// #include <string>
// #include <iostream>
// #include <vector>

using namespace std;

string minWindow(string s, string t);

void TestMinWindow()
{
    // string result = minWindow("ADOBECODEBANC", "ABC");
    string result = minWindow("cabwefgewcwaefgcf", "cae");
    cout << "after function" << endl;
    cout << "result2 is " << result << endl;
}

// Version: violence
string minWindow(string s, string t)
{
    string result = "";

    int sSize = s.size(), tSize = t.size();
    if (sSize < tSize)
        return result;

    vector<int> auxiliaryVec = vector<int>(58, 0);
    vector<int> tVec = vector<int>(58, 0);

    for (int i = 0; i != tSize; ++i)
        tVec[t[i] - 'A']++;

    for (int length = tSize; length <= sSize; ++length)
    {
        for (int i = 0; (i + length - 1) < sSize; ++i)
        {
            for (int &count : auxiliaryVec)
                count = 0;

            for (int j = 0; j != length; ++j)
                auxiliaryVec[s[i + j] - 'A']++;

            bool found = true;
            for (int j = 0; j != 58; ++j)
            {
                if (tVec[j] != 0 && tVec[j] > auxiliaryVec[j])
                {
                    found = false;
                    break;
                }
            }

            if (found)
            {
                result = s.substr(i, length);
                return result;
            }
        }
    }

    return result;
}
