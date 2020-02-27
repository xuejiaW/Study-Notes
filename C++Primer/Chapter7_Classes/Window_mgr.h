#ifndef __WINDOWMGR__
#define __WINDOWMGR__

#include <vector>
#include "Screen.h"

using std::vector;

class Window_mgr
{
public:
    using ScreenIndex = vector<Screen>::size_type;
    void Clear(ScreenIndex index);

private:
    vector<Screen> screens{Screen(5, 5, 'a')};
};

#endif