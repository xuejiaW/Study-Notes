#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;
using std::runtime_error;
using std::string;
using std::vector;

int getNum();
void TestStatementScope();
void Exercise_5_14();
void TestTraditionalFor();
void Exercise_5_17();
void Exercise_5_20();
void TestGoto();
void TestTryCatch();

int main()
{
    // TestStatementScope();
    // Exercise_5_14();
    // TestTraditionalFor();
    // Exercise_5_17();
    // Exercise_5_20();
    // TestGoto();
    TestTryCatch();
}

void TestTryCatch()
{

    int salesNum1, salesNum2;
    while (cin >> salesNum1 >> salesNum2)
    {
        try
        {
            if (salesNum1 < 0 || salesNum2 < 0)
            {
                throw runtime_error("num can't be less than 0");
            }
            int total = salesNum1 + salesNum2;
            cout << "Total num is " << total << endl;
        }
        catch (runtime_error err)
        {
            cout << err.what() << ", try again?" << endl;
            char c;
            cin >> c;

            if (c == 'n')
                break;
        }
    }

    /*
    20 11
    Total num is 31
    -1 25
    num can't be less than 0, try again?
    y
    22 20
    Total num is 42
    -2 1
    num can't be less than 0, try again?
    n
    */
}

void TestGoto()
{

begin:
    int sz = getNum();
    if (sz <= 0)
        goto begin;

    int val;
    int print1;
    cin >> val;
    if (val == 0)
        goto print0;
    else
        goto print1;

print0:
    cout << "This is 0" << endl;
print1:
    cout << "This is 1" << endl;
}

void Exercise_5_20()
{
    string input, lastInput;
    bool occurTwice = false;
    while (cin >> input)
    {
        if (input == lastInput)
        {
            occurTwice = true;
            break;
        }
        lastInput = input;
    }

    if (occurTwice)
        cout << "twice input is " << input << endl;
    else
        cout << "There is no twice input" << endl;
}

void Exercise_5_17()
{
    vector<int> v1 = {0, 1, 1, 2};
    vector<int> v2 = {0, 1, 1, 2, 3, 5, 8};

    bool equal = true;
    for (decltype(v1.size()) i = 0, j = 0; i != v1.size() && j != v2.size(); ++i, ++j)
    {
        if (v1[i] != v2[j])
        {
            equal = false;
            break;
        }
    }
    cout << equal << endl;
}

void TestTraditionalFor()
{
    vector<int> v{1, 2, 3};
    for (decltype(v.size()) i = 0, sz = v.size(); i != sz; ++i)
    {
        v.push_back(v[i]);
    }
    for (auto &val : {1, 2, 3})
    {
        cout << val << " " << endl;
    }
    cout << endl;
    /*
    1
    2
    3
    1
    2
    3
    */
}

void Exercise_5_14()
{
    string input, lastInput, maxInput;
    int repeatTimes = 0;
    int maxRepeatTimes = 0;
    while (cin >> input)
    {
        repeatTimes = lastInput == input ? (repeatTimes + 1) : repeatTimes;
        if (repeatTimes > maxRepeatTimes)
        {
            maxRepeatTimes = repeatTimes;
            maxInput = input;
        }

        lastInput = input;
    }
    cout << "max input is " << maxInput << ",time is " << maxRepeatTimes;
}

void TestDefineVariableInBodyOfSwitch()
{
    int val = 0;
    switch (val)
    {
    case 1:
        // string file_name; //error, default initialization, and the initialization may be bypassed
        // int ival = 0;//error, the initialization may be bypassed
        int jval; //int is build-in type and this is in function so it isn't initialiazed
        break;
    case 0:
        jval = 2;
        break;
    default:
        break;
    }

    switch (val)
    {
    case 1:
    {
        // string file_name; //error, default initialization, and the initialization may be bypassed
        // int ival = 0;//error, the initialization may be bypassed
        int jval; //int is build-in type and this is in function so it isn't initialiazed
        break;
    }
    case 0:
        // jval = 2;//error, jval is in another code scope
        break;
    default:
        break;
    }
}

int getNum()
{
    int j = 0;
    cin >> j;
    return j;
}

void TestStatementScope()
{
    while (int i = getNum())
    {
        cout << "i is " << i << endl;
    }
    // i = 0; //error, out of scope
}