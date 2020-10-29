#include "Input.h"

Input *Input::instance = nullptr;

Input::Input()
{
    ClearInputState();
    for (bool &key : keys)
        key = false;
    anyKey = false;
}

Input::~Input() {}

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
        anyKeyDown = true;
        anyKey = true;
        keysDown[key] = true;
        keys[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        anyKeyUp = true;
        anyKey = false;
        keysUp[key] = true;
        keys[key] = false;
    }
}

void Input::HandleCursorPos(double xPos, double yPos)
{
    mousePos[0] = xPos;
    mousePos[1] = yPos;
}

bool Input::GetKey()
{
    return anyKey;
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

bool Input::GetMouseButtonDown(int key)
{
    return mouseButtonDown[key];
}
bool Input::GetMouseButtonUp(int key)
{
    return mouseButtonUp[key];
}
bool Input::GetMouseButton(int key)
{
    return mouseButton[key];
}
glm::vec3 Input::GetMousePosition()
{
    return mousePos;
}

void Input::ClearInputState()
{
    for (bool &key : keysDown)
        key = false;
    for (bool &key : keysUp)
        key = false;
    for (bool &key : mouseButtonDown)
        key = false;
    for (bool &key : mouseButtonUp)
        key = false;

    anyKeyDown = false;
    anyKeyUp = false;
}