#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>

using namespace std;

struct Sales_data
{
    std::string bookNo;
    unsigned units_sold;
    double revenue;
};

#endif