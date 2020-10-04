#pragma once

#include "Component.h"

class Camera;

class CameraController : public Component
{
public:
    CameraController(Camera* target);
    virtual void Update();
    ~CameraController();

private:
    Camera *targetCamera;
};