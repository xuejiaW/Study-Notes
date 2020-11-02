#include "GO_Camera.h"
#include "../Scene.h"

GO_Camera::GO_Camera() : GameObject()
{
    name = "GO_Camera";
    Debug::Log("Before Create Transform for GO_Camera");
    this->transform = new Transform();
    AddComponent(transform);
    Debug::Log("After Create Transform for GO_Camera");

    transform->SetPosition(vec3(0, 0, 3));
    transform->SetEulerAngle(vec3(0, -90, 0));

    Debug::Log("Before Create Camrea for GO_Camera");
    this->camera = new Camera(scene->GetScreenRatio());
    AddComponent(camera);
    Debug::Log("After Create Camera for GO_Camera");

    this->cameraController = new CameraController(this->camera);
    AddComponent(cameraController);
    Debug::Log("After Create cameraController for GO_Camera");
}

GO_Camera::~GO_Camera() {}