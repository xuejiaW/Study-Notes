#include "Input.h"

Input *Input::instance = nullptr;

Input::Input()
{
    ClearInputState();
    for (bool &key : keys)
        key = false;
}

Input::~Input() { }

Input *Input::GetInstance()
{
    if (Input::instance == nullptr)
        Input::instance = new Input();
    return Input::instance;
}

void Input::HandleMouseButton(int button, int action, int modes)
{
    if (action == GLFW_PRESS)
    {
        mouseButtonDown[button] = true;
        mouseButton[button] = true;
    }
    else
    {
        mouseButtonUp[button] = true;
        mouseButton[button] = false;
    }
}

void Input::HandleKey(int key, int scanCode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        keysDown[key] = true;
        keys[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        keysUp[key] = true;
        keys[key] = false;
    }
}

bool Input::GetKeyDown(int key)
{
    return keysDown[key];
}

bool Input::GetKeyUp(int key)
{
    return keysUp[key];
}

bool Input::GetKey(int key)
{
    return keys[key];
}

void Input::ClearInputState()
{
    for (bool &key : keysDown)
        key = false;
    for (bool &key : keysUp)
        key = false;
}