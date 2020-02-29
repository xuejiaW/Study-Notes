#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

struct Test
{
    vector<int> value;
};

struct First
{
    int memi = 0;
    int getMem = 0;
};

struct Second
{
    int memi = 0;
    int getMem = 0;
};

struct NotDefined;

struct TestNotDefined
{
    NotDefined *np;
    static NotDefined ns;
    NotDefined functionAboutNotDefine(NotDefined);
};

struct X
{
    friend void f();
    // X() { f(); } //error
    void g();
    void h();
};

// void X::g() { return f(); } //error

void f() {}

void X::h() { return f(); }

typedef double Money;

// void testTypedef()
// {
//     Money i;
//     typedef int Money;
//     Money j;
// }
string bal;
class Account
{
public:
    Money balnce() { return bal; }

private:
    typedef float Money;
    Money bal;
};

class ConstRef
{
private:
    ConstRef(int ii) : ci(ii), ri(ii)
    {
        i = ii;
    }

    // ConstRef(int ii) //error
    // {
    //     ri = i;
    //     ci = i;
    //     i = ii;
    // }

public:
    int i;
    const int ci;
    int &ri;
};

class Num
{
public:
    Num(int val) : j(val), i(j) {}
    void Print()
    {
        cout << "i value is: " << i << endl;
        cout << "j value is: " << j << endl;
    }

private:
    int i;
    int j;
};

class NoDefault
{
public:
    NoDefault(const string);
};

struct A
{
    NoDefault my_mem;
};

// A a;
// A a = A();

struct B
{
    // B(){}; //error
    B() : b_member(""){};
    NoDefault b_member;
};

struct Data
{
    int ival;
    string s;
};

class Account_S
{
public:
    typedef double RateD;
    // Account_S() : interestRate(0) //error
    // {
    //     interestRate = 0;
    // }

    Account_S()
    {
        interestRate = 0;
    }

    // void TestDefaultValue(double a = amount)
    // {
    // }//can not use member variable as default parameters

    void TestDefaultValue(double a = interest)
    {
    }//can use member variable as default parameters


    void calculate()
    {
        amount += amount * interestRate;
    }

    static double rate()
    {
        return interestRate;
    }

    static void rate(double);

private:
    string owner;
    double amount;
    // static double interestRate = 2;
    static RateD interestRate;
    static double interest;
    static const double cRate;
    static double InitRate() { return 0; }
    // static double CInitRate() const; //error static member function can't be const
};

Account_S::RateD Account_S::interestRate = InitRate();
double Account_S::interest = InitRate();

void Account_S::rate(double rate)
{
    interestRate = rate;
}