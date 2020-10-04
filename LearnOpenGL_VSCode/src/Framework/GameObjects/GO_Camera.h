#pragma once
#include "GameObject.h"
#include "../Components/Transform.h"
#include "../Components/Camera.h"
#include "../Components/CameraController.h"

class GO_Camera : public GameObject
{
public:
    GO_Camera();
    ~GO_Camera();

private:
    Transform *transform = nullptr;
    Camera *camera = nullptr;
    CameraController *cameraController = nullptr;
};