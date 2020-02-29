#pragma once
#ifndef __SALESDATA__
#define __SALESDATA__
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::string;

class Sales_data
{

    friend Sales_data add(const Sales_data &, const Sales_data &);
    friend ostream &print(ostream &, const Sales_data &);
    friend istream &read(istream &, Sales_data &);

public:
    Sales_data();
    explicit Sales_data(const string &s);
    Sales_data(const string &s, unsigned n, double p);
    Sales_data(istream &);

public:
    //Member function
    string isbn() const { return bookNo; }
    // string isbn() { return bookNo; } // should be const
    Sales_data &combine(const Sales_data &);
    Sales_data &combine(const Sales_data &) const;

private:
    double avg_Price() const;
    //Member variable
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0;
};

//nonmember but related function

Sales_data add(const Sales_data &, const Sales_data &);
ostream &print(ostream &, const Sales_data &);
istream &read(istream &, Sales_data &);

inline Sales_data::Sales_data(const string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p * n)
{
    // cout << "Constructor with 3 parameters" << endl;
}

inline Sales_data::Sales_data() : Sales_data("", 0, 0)
{
    // cout << "Constructor with no Parameters" << endl;
}
inline Sales_data::Sales_data(const string &s) : Sales_data(s, 0, 0)
{
}
// inline Sales_data::Sales_data(istream &is) : Sales_data(),revenue(0) { read(is, *this); }
inline Sales_data::Sales_data(istream &is) : Sales_data()
{
    read(is, *this);
}

#endif