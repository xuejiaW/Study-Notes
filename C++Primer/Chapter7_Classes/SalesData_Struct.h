#pragma once
#ifndef __SALESDATA_STRUCT__
#define __SALESDATA_STRUCT__
#include <iostream>
#include <string>

using std::istream;
using std::ostream;
using std::string;

struct Sales_data
{
    Sales_data() = default;
    Sales_data(const string &s);
    Sales_data(const string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p * n) {}
    Sales_data(istream &);

    //Member function
    string isbn() const { return bookNo; }
    // string isbn() { return bookNo; } // should be const

    Sales_data &combine(const Sales_data &);
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

inline Sales_data::Sales_data(const string &s) : bookNo(s) {}

#endif