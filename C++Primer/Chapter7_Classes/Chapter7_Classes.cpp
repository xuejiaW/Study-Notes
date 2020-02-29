#include <iostream>
// #include "SalesData_Struct.h"
#include "SalesData.h"
#include "Screen.h"
#include "Test.h"

using std::cout;
using std::endl;

void TestThisPointer();
void TestSynthesizedAssignment();
void TestReturnThisPointer();
void TestClassType();
void TestClassScope();
void TestMemberInitializationOrder();
void TestConstructorsRevisited();
void TestAggregateClasses();

int main()
{
    // TestThisPointer();
    // TestSynthesizedAssignment();
    // TestReturnThisPointer();
    // TestClassType();
    // TestClassScope();
    // TestMemberInitializationOrder();
    // TestConstructorsRevisited();
}

void TestStaticMember()
{
    double r = Account_S::rate();
    Account_S ac1;
    Account_S *ac2 = &ac1;
    r = ac1.rate();
    r = ac2->rate();
}

void TestAggregateClasses()
{
    Data val1{0, "Anna"};
    Data val2{0};
}

void TestConstructorsRevisited()
{
    string null_book = "9999";
    Sales_data item;
    // item.combine(null_book);// error, when constructor is explicit
    item.combine(Sales_data(null_book));
    item.combine(static_cast<Sales_data>(null_book));
    // item.combine("9999"); // this action needs two step conversion,so it fails
}

void TestMemberInitializationOrder()
{
    Sales_data s;
    Num n(2);
    n.Print();
}

void TestClassScope()
{
    Screen s(10, 2, ' ');
    s.dummyFcn(3);
}

void TestClassType()
{
    First first;
    Second sec;
    first.memi = 2;

    // sec = first; //Error

    Second *sp = reinterpret_cast<Second *>(&first);
    cout << "sp value is " << sp->memi << endl;
}

void TestSynthesizedAssignment()
{
    Test firstOne;
    firstOne.value = {1, 2, 3};
    Test secondOne;
    secondOne = firstOne;
    firstOne.value[0] = 4;

    cout << "First one value is: " << endl;
    for (int i : firstOne.value)
        cout << i << " ";

    cout << endl;

    cout << "Second one value is: " << endl;
    for (int i : secondOne.value)
        cout << i << "";
}

void TestReturnThisPointer()
{
    Screen sc(5, 5, 'c');
    sc.move(4, 0).set('a');
    cout << "content is " << sc.get() << endl;
    sc.move_copy(4, 0).set('b');
    cout << "content is " << sc.get() << endl;

    // cout << endl;
    cout << "content is: " << endl;
    sc.Display(cout);          //correct
    sc.Display(cout).set('a'); // error when there is no nonconst overwrite
    cout << endl;

    /*
    content is a
    content is a
    content is:
    ccccccccccccccccccccacccc
    */
}

void TestThisPointer()
{
    Sales_data total;
    total.isbn();
    const Sales_data cTotal;
    // cTotal.isbn();//error
}