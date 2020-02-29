#include "Screen.h"
#include <iostream>

using std::cout;
using std::endl;

Screen::Screen(pos ht, pos wd, char c) : height(ht), width(wd), content(ht * wd, c)
{
}

void Screen::ChangeAccessCtr() const
{
    ++accessCtr;
}

void Screen::do_display(ostream &os) const
{
    os << content;
}

int height = 5;
void Screen::dummyFcn(pos height)
{
    cout << "height is " << height << endl;
    cout << "Screen height is " << this->height << endl;
    cout << "Global height is " << ::height << endl;
}