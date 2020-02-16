#include <iostream>

using std::cout;
using std::endl;

void TestOrderOfEvaluation();
void TestArithmeticOperations();
void TestRelationalOperations();
void TestAssignmentOpeartions();

int main()
{
    // TestOrderOfEvaluation();
    // TestArithmeticOperations();
    // TestRelationalOperations();
    TestAssignmentOpeartions();
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