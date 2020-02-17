#include <iostream>
#include <bitset>
#include <vector>
#include <string>

using std::bitset;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

void TestOrderOfEvaluation();
void TestArithmeticOperations();
void TestRelationalOperations();
void TestAssignmentOpeartions();
void TestIncrementAndDecrement();
void TestConditionalOperations();
void Exercise4_21();
void TestSizeOf();
void TestComma();
void TestTypeConversions();

int main()
{
    // TestOrderOfEvaluation();
    // TestArithmeticOperations();
    // TestRelationalOperations();
    // TestAssignmentOpeartions();
    // TestIncrementAndDecrement();
    // TestConditionalOperations();
    // Exercise4_21();
    // TestSizeOf();
    // TestComma();
    TestTypeConversions();
}

void TestTypeConversions()
{
    auto b = 12 + 'a' + 12L;

    int i = 10, j = 3;
    double slope = i / j;
    cout << "slope is " << slope << endl;
    slope = static_cast<double>(i) / j;
    cout << "slope is " << slope << endl;

    /*
    slope is 3
    slope is 3.33333
    */

    void *p = &slope;
    double *dp = static_cast<double *>(p);
    cout << "slope is " << (*dp) << endl;

    /*
    slope is 3.33333
    */

    const int *value1 = &i;
    // int *valueP = value;
    int *value2 = const_cast<int *>(value1);
    cout << "value1 is " << (*value1) << endl;
    *value2 = 3;
    cout << "value1 is " << (*value1) << endl;
    cout << "value2 is " << (*value2) << endl;

    /*
    value1 is 10
    value1 is 3
    value2 is 3
    */

    int *ip = &i;
    char *cstr = reinterpret_cast<char *>(ip);
    string str = cstr;
    cout << "str is " << str << endl;

    char *pc;
    int i = int(*pc);
    i = (int)(*pc);

    const string *ps;
    void *pv;

    pv = static_cast<void *>(const_cast<string *>(ps));
    pv = (void *)ps;
}

void TestComma()
{
    int x = 1, y = 3, i;
    cin >> i;
    (i > 0) ? ++x, ++y : --x, --y;
    cout << "x is " << x << ", y is " << y << endl;
    int a = (--x, --y);

    /*
    2
    x is 2, y is 3
    */

    /*
   -1
    x is 0, y is 2
   */
}

void TestSizeOf()
{
    string s = "ABCD", ss = "", *sp = &s;
    cout << sizeof(string) << endl; //32
    cout << sizeof ss << endl;      //32
    cout << sizeof s << endl;       //32
    cout << sizeof sp << endl;      //8
    cout << sizeof *sp << endl;     //32

    cout << sizeof s.size() << endl; //8
    cout << sizeof(size_t) << endl;  //8

    int arr[3]{1, 2, 3};
    cout << sizeof(arr) << endl; //12
    int arrr[4]{};
    cout << sizeof(arrr) << endl; //16
}

void Exercise4_21()
{
    vector<int> intList{1, 2, 3, 4, 5, 6};
    for (auto &i : intList)
    {
        i = i & 0x1 ? i * 2 : i;
    }

    for (auto &i : intList)
    {
        cout << i << " " << endl;
    }
}

void TestConditionalOperations()
{
    int grade;
    cin >> grade;
    string final = (grade > 90) ? "High Pass" : (grade < 60) ? "fail" : "pass";
    cout << "Final is " << final << endl;

    cout << ((grade < 60) ? "fail" : "pass");
    cout << endl;
    cout << (grade < 60) ? "fail" : "pass";
    cout << endl;
    // cout << grade < 60 ? "fail" : "pass"; //Error

    /*
    55
    Final is fail
    fail
    1
    */

    // string s("string");
    // string p1 = s + s[s.size() - 1] == 's' ? "" : "s";
}

void TestIncrementAndDecrement()
{
    int i = 0, j;
    cout << "i is " << i << ", j is " << j << endl;
    j = ++i;
    cout << "i is " << i << ", j is " << j << endl;
    j = i++;
    cout << "i is " << i << ", j is " << j << endl;

    /*
    i is 0, j is 0
    i is 1, j is 1
    i is 2, j is 1
    */

    string s = "abcdefg";
    auto beg = s.begin();
    while (beg != s.end() && !isspace(*beg))
    {
        *beg = toupper(*beg++);
    }
    cout << s << endl;

    /*
    aAAAAAA 
    */
}

void TestAssignmentOpeartions()
{
    int i;
    double d;
    i = d = 3.5;
    cout << "i is " << i << ", d is " << d << endl;
    d = i = 3.5;
    cout << "i is " << i << ", d is " << d << endl;

    /*
    i is 3, d is 3.5
    i is 3, d is 3
    */
}

void TestRelationalOperations()
{
    int i = 3, j = 2, k = 3;
    if (i < j < k)
        cout << "enter case 1";
}

void TestArithmeticOperations()
{
    bool b = true;
    bool b2 = -b;
    cout << "b2 is " << b2;

    /*
    b2 is 1
    */

    short short_value = 32767;
    short_value++;
    cout << "short value is " << short_value << endl;

    /*
    b2 is 1short value is -32768
    */
}

int f1()
{
    int value = 3;
    cout << "f1 value is " << value << endl;
    return value;
}

int f2()
{
    int value = 3;
    cout << "f2 value is " << value << endl;
    return value;
}

void TestOrderOfEvaluation()
{
    int i = f1() * f2();
    cout << "i value is " << i << endl;

    cout << i << " " << ++i << endl;
}