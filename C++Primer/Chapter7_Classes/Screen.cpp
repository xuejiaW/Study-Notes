#include "Screen.h"

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