#include "CameraController.h"
#include "../Input.h"
#include "Camera.h"
#include "../Scene.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

double lastX = 0.0f;
double lastY = 0.0f;
bool waitingFirstClick = true;
double mouseSensitivity = 0.1;

CameraController::CameraController(Camera *target) : targetCamera(target)
{
    input = Input::GetInstance();
}

void CameraController::Update()
{
    if (targetCamera == nullptr)
        return;

    if (input->GetKey())
        HandleKeyboardEvent();

    if (input->GetMouseButtonUp(1))
        waitingFirstClick = true;
    if (input->GetMouseButton(1))
        HandleMouseEvent();
}

void CameraController::HandleKeyboardEvent()
{
    glm::vec3 cameraPos = targetCamera->GetPosition();
    glm::vec3 forward = targetCamera->GetForward();
    glm::vec3 right = targetCamera->GetRight();
    glm::vec3 up = targetCamera->GetUp();
    float speed = 2.5f * Scene::GetInstance()->GetFrameTime();
    if (input->GetKey(GLFW_KEY_W))
        cameraPos += speed * forward;
    if (input->GetKey(GLFW_KEY_A))
        cameraPos -= speed * right;
    if (input->GetKey(GLFW_KEY_S))
        cameraPos -= speed * forward;
    if (input->GetKey(GLFW_KEY_D))
        cameraPos += speed * right;
    if (input->GetKey(GLFW_KEY_Q))
        cameraPos += speed * up;
    if (input->GetKey(GLFW_KEY_E))
        cameraPos -= speed * up;

    targetCamera->SetPosition(cameraPos);
}

void CameraController::HandleMouseEvent()
{
    glm::vec3 mousePos = input->GetMousePosition();
    glm::vec3 eulerAngle = targetCamera->GetEulerAngle();

    if (waitingFirstClick)
    {
        lastX = mousePos[0];
        lastY = mousePos[1];
        waitingFirstClick = false;
    }

    float xOffset = (mousePos[0] - lastX) * mouseSensitivity;
    float yOffset = (lastY - mousePos[1]) * mouseSensitivity;

    lastX = mousePos[0];
    lastY = mousePos[1];

    eulerAngle[1] += xOffset;
    eulerAngle[0] += yOffset;

    if (eulerAngle[0] > 89.0)
        eulerAngle[0] = 89.0;
    if (eulerAngle[0] < -89.0)
        eulerAngle[0] = -89.0;

    targetCamera->SetEulerAngle(eulerAngle);
}

CameraController::~CameraController()
{
}