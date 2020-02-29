#ifndef __WINDOWMGR__
#define __WINDOWMGR__

#include <vector>

class Screen;
using std::vector;

class Window_mgr
{
public:
    using ScreenIndex = vector<Screen>::size_type;
    void Clear(ScreenIndex index);
    ScreenIndex addScreen(const Screen &s);

private:
    vector<Screen> screens;
};

#endif