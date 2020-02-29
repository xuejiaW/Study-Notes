#ifndef __SCREEN__
#define __SCREEN__

#include <string>
#include <iostream>

#include "Window_mgr.h"

using std::istream;
using std::ostream;
using std::string;

class Screen
{
    friend void Window_mgr::Clear(ScreenIndex);

public:
    // pos i = 0; //error, the pos hasn't been
    typedef string::size_type pos;
    // using pos = string::size_type; // same with above

    Screen() = default;
    Screen(pos ht, pos wd, char c);

    void ChangeAccessCtr() const;

    char get() const { return content[cursor]; }
    inline char get(pos ht, pos wd) const;

    inline Screen &move(pos ht, pos wd);
    inline Screen move_copy(pos ht, pos wd);

    inline Screen &set(char c);
    inline Screen &set(pos ht, pos wd, char c);

    inline const Screen &Display(ostream &) const;
    inline Screen &Display(ostream &);

    void dummyFcn(pos height);

private:
    mutable size_t accessCtr = 0;
    pos cursor = 0, height = 0, width = 0;
    string content;

    void do_display(ostream &os) const;
};

Screen &Screen::move(pos ht, pos wd)
{
    pos row = ht * width;
    cursor = row + wd;
    return *this;
}

const Screen &Screen::Display(ostream &os) const
{
    do_display(os);
    return *this;
}

Screen &Screen::Display(ostream &os)
{
    do_display(os);
    return *this;
}

Screen Screen::move_copy(pos ht, pos wd)
{
    pos row = ht * width;
    cursor = row + wd;
    return *this;
}

Screen &Screen::set(char c)
{
    content[cursor] = c;
    return *this;
}

Screen &Screen::set(pos ht, pos wd, char c)
{
    pos row = ht * width;
    content[row + wd] = c;
    return *this;
}

inline char Screen::get(pos ht, pos wd) const
{
    pos row = ht * width;
    return content[row + wd];
}

#endif