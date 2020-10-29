#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Input
{
public:
    Input(/* args */);
    ~Input();

    void HandleMouseButton(int button, int action, int mods);
    void HandleKey(int key, int scanCode, int action, int mods);
    void HandleCursorPos(double xPos, double yPos);
    void ClearInputState();
    bool GetKey();
    bool GetKeyDown(int key);
    bool GetKeyUp(int key);
    bool GetKey(int key);
    bool GetMouseButtonDown(int key);
    bool GetMouseButtonUp(int key);
    bool GetMouseButton(int key);
    glm::vec3 GetMousePosition();

    static Input *GetInstance();

private:
    static Input *instance;
    glm::vec3 mousePos;
    bool anyKey;
    bool anyKeyDown;
    bool anyKeyUp;
    bool keys[1024];
    bool keysDown[1024];
    bool keysUp[1024];
    bool mouseButtonDown[10];
    bool mouseButtonUp[10];
    bool mouseButton[10];
};
