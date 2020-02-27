#include "Window_mgr.h"

void Window_mgr::Clear(Window_mgr::ScreenIndex index)
{
    Screen &s = screens[index];
    s.content = string(s.height * s.width, ' ');
}
