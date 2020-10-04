#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include "Component.h"

using glm::mat4;
using glm::vec3;

class Transform;
const glm::vec3 worldUp = glm::vec3(0, 1, 0);

class Camera : public Component
{
public:
    Camera();

    Camera(float ratio, float fov = 60.0f, float nearClipping = 0.1f, float farClipping = 100.0f);

    mat4 GetViewMatrix();
    mat4 GetProjectionMatrix();
    vec3 GetForward();
    vec3 GetPosition();
    vec3 GetEulerAngle();
    vec3 GetRight();
    vec3 GetUp();

    void SetFOV(float);
    void SetRatio(float);
    void SetNearClipping(float);
    void SetFarClipping(float);
    void SetPosition(vec3);

    void UpdateCameraViewMatrix();
    void UpdateCameraProjectionMatrix();
    ~Camera();

private:
    Transform *transform;
    Transform *GetTransform();

    float fieldOfView;
    float ratio;
    float nearClipping;
    float farClipping;

    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};
