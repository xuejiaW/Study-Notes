#include <iostream>
#include <vector>

using std::vector;

struct Test
{
    vector<int> value;
};

struct First
{
    int memi = 0;
    int getMem = 0;
};

struct Second
{
    int memi = 0;
    int getMem = 0;
};

struct NotDefined;

struct TestNotDefined
{
    NotDefined *np;
    static NotDefined ns;
    NotDefined functionAboutNotDefine(NotDefined);
};