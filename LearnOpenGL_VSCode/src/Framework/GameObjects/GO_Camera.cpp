#include "GO_Camera.h"
#include "../Scene.h"

GO_Camera::GO_Camera() : GameObject()
{
    name = "GO_Camera";
    this->transform = new Transform();
    AddComponent(transform);

    transform->SetPosition(vec3(0, 0, 3));
    transform->SetEulerAngle(vec3(0, -90, 0));

    this->camera = new Camera(scene->GetScreenRatio());
    AddComponent(camera);

    this->cameraController = new CameraController(this->camera);
    AddComponent(cameraController);
}

GO_Camera::~GO_Camera() {}