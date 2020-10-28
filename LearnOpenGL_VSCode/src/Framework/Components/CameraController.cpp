#include "CameraController.h"
#include "../Input.h"
#include "Camera.h"
#include "../Scene.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

CameraController::CameraController(Camera *target) : targetCamera(target)
{
}

void CameraController::Update()
{
    if (targetCamera == nullptr)
        return;

    glm::vec3 cameraPos = targetCamera->GetPosition();
    glm::vec3 forward = targetCamera->GetForward();
    glm::vec3 right = targetCamera->GetRight();
    float speed = 2.5f * Scene::GetInstance()->GetFrameTime();
    if (Input::GetInstance()->GetKey(GLFW_KEY_W))
    {
        cameraPos += speed * forward;
    }
    if (Input::GetInstance()->GetKey(GLFW_KEY_A))
    {
        cameraPos -= speed * right;
    }
    if (Input::GetInstance()->GetKey(GLFW_KEY_S))
    {
        cameraPos -= speed * forward;
    }
    if (Input::GetInstance()->GetKey(GLFW_KEY_D))
    {
        cameraPos += speed * right;
    }

    targetCamera->SetPosition(cameraPos);
}

CameraController::~CameraController()
{
}