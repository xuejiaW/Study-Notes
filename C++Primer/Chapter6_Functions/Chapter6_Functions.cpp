#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "GetNum.h"
#include <cstdlib>
#include <cassert>

using std::begin;
using std::cin;
using std::cout;
using std::end;
using std::endl;
using std::initializer_list;
using std::rand;
using std::runtime_error;
using std::string;
using std::vector;

void TestLocalObject();
void TestLocalObject();
void pareNoName(int, float fval);
void TestStaticObjects();
void Exercise6_10();
void Exercise_6_12();
void Swap(int *val1, int *val2);
void Swap(int &val1, int &val2);
void func(const int i);
void TestConstParametersAndArguments();
void funs(string &s);
void funss(const string &s);
void print(const int[10]);
void print(const char cp[]);
void print(const int *beg, const int *end);
void print(const int *beg, size_t size);
void print(int (&arr)[5]);
void print(int (*matrix)[2], int rowSize);
void print(int **matrix, int rowSize, int columnSize);
void TestArrayParameters();
void error_msg(initializer_list<string> il);
void TestVaryingParameters();
string screen(int, int, char = '*');
// string screen(int, int, char = ' ');
string screen(int = 24, int = 80, char);
void TestDefaultArgument();
void TestPreprocessorVariable();
void TestFunctionPointers();

int main(int argc, char **argv)
{
    // int a = 3, b = 2;
    // assert(a < b);
    // cout << "argc count is " << argc << endl;
    // for (int i = 0; i != argc; ++i)
    // {
    //     cout << "arg is " << argv[i] << endl;
    // }

    // pareNoName(0.1f);//Although int doesn't have name, we still must assign it
    // pareNoName(3, 0.1f);
    // TestLocalObject();
    // TestStaticObjects();
    // cout << GetNum() << endl;
    // Exercise6_10();
    // TestConstParametersAndArguments();
    // TestArrayParameters();
    // TestVaryingParameters();
    // screen();
    // TestDefaultArgument();

    // cout << GetDoubleNum();
    // TestPreprocessorVariable();
    TestFunctionPointers();
}

//Method1: use alias
using F = int(int *, int);      //F is Function type,retun type is int
using FF = int *(int *, int);   //F is Function type,retun type is pointe to int
using PF = int (*)(int *, int); //FP is pointer to Function type
PF f1(int);
// F f1(int); //error, function type can not be return type
F *f1(int);

//Method 2: directly
//like directly define return is pointer to array, which looks like
//int (*f1(int)) [10];
int (*f1(int))(int *, int);

//Method 3: use trailing return
auto f1(int) -> int (*)(int *, int);

//Method4: use decltype
int func1(int *, int);
decltype(func1) *f1(int);

bool lengthCompare(const string &s1, const string &s2)
{
    return s1.size() > s2.size();
}

void TestFunctionPointers()
{
    bool (*fp)(const string &, const string &) = lengthCompare;
    // bool (*fp)(const string &, const string &) = &lengthCompare;//equal to above

    bool b1 = fp("hello", "goodbyte");
    bool b2 = (*fp)("hello", "goodbyte");       // equal to above
    bool b3 = lengthCompare("hello", "goodby"); //equal ro above
    cout << "b1: " << b1 << endl;
    cout << "b2: " << b2 << endl;
    cout << "b3: " << b3 << endl;
}

void TestPreprocessorVariable()
{
    cout << "Function is " << __func__ << endl;
    cout << "File is " << __FILE__ << endl;
    cout << "Line is " << __LINE__ << endl;
    cout << "Time is " << __TIME__ << endl;
    cout << "Dateis " << __DATE__ << endl;
}

// int GetNum()
// {
//     return 10;
// }

void Debug(const string &msg)
{
#ifndef NDEBUG
    cout << msg << endl;
#endif
}

inline double GetDoubleNum()
{
    return 4.15;
}

int vall = 20;
char cc = 'a';

void printDefaultArgument(int ran = rand(), int w = vall, char c = cc)
{
    cout << "random is " << ran << ", w is " << w << ", c is " << c << endl;
}

void TestDefaultArgument()
{
    printDefaultArgument();
    vall = 30;
    char cc = 'b';
    printDefaultArgument();
}

string screen(int width, int height, char c)
{
    cout << "width is " << width << ", height is " << height << ", c is " << c << endl;
    return "";
}

//// Test for scope hiding
// string read() { return "readed"; }
// void print(const string &s) { cout << s << endl; }
// void print(double d) { cout << d << endl; }
// void fooBar(int ival)
// {
//     bool read = false;
//     // string s = read();//error, read() is hidden, in this scope read is a bool variable
//     string s = ::read(); //ok,use :: to indicate search name is global scope

//     // Decalare a function in the inner scope.This action is rare in practice.
//     //Here we only use this to illustrate scope hidding
//     void print(int);
//     // print("value :");//error, print(const string &s) is hidden.
//     print(ival);
//     print(3.14); //ok, but it will call print(int)
// }

inline const string &shorterString(const string &s1, const string &s2)
{
    return s1.size() < s2.size() ? s1 : s2;
}

string &shorterString(string &s1, string &s2)
{
    const string &r = shorterString(const_cast<const string &>(s1), const_cast<const string &>(s2));
    return const_cast<string &>(r);
}

vector<string> process()
{
    return {"A", "Bb", "c"};
}

typedef int arrt[10];
// using arrt = int[10];// equally

// arrt *funcArray();

// int (*funcArray())[10];

// auto funcArray() -> int (*)[]{

// };

int odd[] = {1, 2, 3, 4, 5};
int even[] = {0, 2, 4, 6, 8};
decltype(odd) *funcArray()
{
    return &odd;
}

char &Get_Val(string &str, string::size_type ix)
{
    return str[ix];
}

// const string &manip()
// {
//     string ret;
//     if (!ret.empty())
//         return ret; //error,return reference of local variable
//     else
//         return "empty"; //error, return reference of a temporary string
// }

string ReturnThePluralVersionOfWord(size_t ctr, const string &word, const string &ending)
{
    return (ctr <= 1) ? word : word + ending;
}

void TestVaryingParameters()
{
    error_msg({"functionX", "abc", "def"});
}

void error_msg(initializer_list<string> il)
{
    for (auto beg = il.begin(); beg != il.end(); ++beg)
    {
        cout << *beg << " ";
    }
    cout << endl;
}

void TestArrayParameters()
{
    int i = 0, j[2] = {0, 1};
    print(&i);
    print(j);

    print("abcd");
    print(begin(j), end(j));
    print(j, end(j) - begin(j));

    int valList[] = {0, 1, 2, 3, 4};
    print(j);
    print(valList);

    cout << "Multidimensional Array:" << endl;
    int mat[3][2] = {{1, 2}, {3, 4}, {5, 6}};
    print(mat, 3);
    cout << "pointer to pointer" << endl;

    //Initial array
    int **matrix = new int *[3];
    for (int i = 0; i != 3; ++i)
    {
        matrix[i] = new int[2];
        matrix[i][0] = 2 * i;
        matrix[i][1] = 2 * i + 1;
    }
    print(matrix, 3, 2);

    //release data
    for (int i = 0; i != 3; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void print(int **matrix, int rowSize, int columnSize)
{
    for (int i = 0; i != rowSize; ++i)
    {
        for (int j = 0; j != columnSize; ++j)
        {
            cout << matrix[i][j] << endl;
        }
    }
}

void print(int (*matrix)[2], int rowSize)
{
    for (int i = 0; i != rowSize; ++i)
    {
        for (int j = 0; j != 2; ++j)
        {
            //cout << matrix[i][j] << endl;
            cout << *((*(matrix + i)) + j) << endl;
        }
    }
}

void print(const char cp[])
{
    if (cp)
    {
        while (*cp)
            cout << *cp++;
    }
    cout << endl;
}

void print(const int *beg, const int *end)
{
    while (beg != end)
        cout << *beg++ << endl;
}

void print(const int *beg, size_t size)
{
    for (size_t i = 0; i != size; ++i)
    {
        cout << *beg++ << endl;
    }
}

void print(int (&arr)[5])
{
    for (auto val : arr)
    {
        cout << val << endl;
    }
}

// void print(const int *)
// {
// }
// void print(const int[])
// {
// }
void print(const int[10]) {}

void TestConstParametersAndArguments()
{
    const int ci = 3;
    int i = 2;
    func(ci);
    func(i);
    /*
    value is 3
    value is 2
    */

    const string ss = "";
    // funs("");//error,can not use literal to initialize string reference
    // funs(ss);//error,can not use const string to initialize string reference
    funss("");
    funss(ss);
}

void funs(string &s) {}
void funss(const string &s) {}

void func(const int i)
{
    cout << "value is " << i << endl;
}

// void func(int i) {}//Error,redefines

void Exercise_6_12()
{
    int val1 = 10, val2 = 5;
    cout << "Val 1 is " << val1 << ", Val2 is " << val2 << endl;
    Swap(val1, val2);
    cout << "Val 1 is " << val1 << ", Val2 is " << val2 << endl;
}

void Swap(int *val1, int *val2)
{
    int temp = (*val1);
    *val1 = *val2;
    *val2 = temp;
}

void Swap(int &val1, int &val2)
{
    int temp = val1;
    val1 = val2;
    val2 = temp;
}

void Exercise6_10()
{
    int val1 = 10, val2 = 5;
    cout << "Val 1 is " << val1 << ", Val2 is " << val2 << endl;
    Swap(&val1, &val2);
    cout << "Val 1 is " << val1 << ", Val2 is " << val2 << endl;
}

int count_calls()
{
    static int ctr = 0;
    return ++ctr;
}

void TestStaticObjects()
{
    for (int i = 0; i != 10; ++i)
    {
        cout << count_calls() << endl;
    }
    /*
    1
    2
    3
    4
    5
    6
    7
    8
    9
    10
    */
}

void f2(void) {}

void pareNoName(int, float fval) {}

int val = 2;
void TestLocalObject()
{
    int val = 3;
    cout << "local val is " << val << endl;
    cout << "global val is " << ::val << endl;

    /*
    local val is 3
    global val is 2
    */
}