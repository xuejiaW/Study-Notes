#include "Debug.h"

void Debug::Log(string description, int value)
{
    cout << description << ": " << value << endl;
}

void Debug::Log(string description, float value)
{
    cout << description << ": " << value << endl;
}

void Debug::Log(string description, vec3 value)
{
    cout << description << ": " << value[0] << " " << value[1] << " " << value[2] << endl;
}

Debug::Debug()
{
}

Debug::~Debug()
{
}