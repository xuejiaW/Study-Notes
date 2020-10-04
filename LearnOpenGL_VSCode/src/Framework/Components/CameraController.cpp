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
    glm::vec3 cameraPos = targetCamera->GetPosition();
    glm::vec3 forward = targetCamera->GetForward();
    float speed = 2.5f * Scene::GetInstance()->GetFrameTime();
    if (Input::GetInstance()->GetKey(GLFW_KEY_W))
    {
        cameraPos += speed * forward;
    }
    if (Input::GetInstance()->GetKey(GLFW_KEY_A))
    {
        cout << "Press W" << endl;
    }
    if (Input::GetInstance()->GetKey(GLFW_KEY_S))
    {
        cameraPos -= speed * forward;
        cout << "Press S" << endl;
    }
    if (Input::GetInstance()->GetKey(GLFW_KEY_D))
    {
        cout << "Press W" << endl;
    }
    targetCamera->SetPosition(cameraPos);
}

CameraController::~CameraController()
{
}