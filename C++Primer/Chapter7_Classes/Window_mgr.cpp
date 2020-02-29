#include "Window_mgr.h"
#include "Screen.h"

void Window_mgr::Clear(ScreenIndex index)
{
    Screen &s = screens[index];
    s.content = string(s.height * s.width, ' ');
}

Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}