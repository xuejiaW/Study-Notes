#pragma once

#include "Component.h"

class Camera;
class Input;

class CameraController : public Component
{
public:
    CameraController(Camera *target);
    virtual void Update();
    ~CameraController();

private:
    Camera *targetCamera = nullptr;
    Input *input = nullptr;
    void HandleKeyboardEvent();
    void HandleMouseEvent();
};