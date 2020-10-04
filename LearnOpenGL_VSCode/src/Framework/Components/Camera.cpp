#include "Camera.h"
#include "Transform.h"

Camera::Camera()
{
    name = "Camera";
}
Camera::Camera(float ratio, float fov, float nearClipping, float farClipping) : Camera()
{
    this->ratio = ratio;
    this->fieldOfView = fov;
    this->nearClipping = nearClipping;
    this->farClipping = farClipping;
}

glm::mat4 Camera::GetViewMatrix()
{
    return viewMatrix;
}
glm::mat4 Camera::GetProjectionMatrix()
{
    return projectionMatrix;
}

vec3 Camera::GetForward() { return forward; }
vec3 Camera::GetRight() { return right; }
vec3 Camera::GetUp() { return up; }
vec3 Camera::GetPosition() { return GetTransform()->GetPosition(); }
vec3 Camera::GetEulerAngle() { return GetTransform()->GetEulerAngle(); }

void Camera::UpdateCameraProjectionMatrix()
{
    projectionMatrix = glm::perspective(fieldOfView, ratio, nearClipping, farClipping);
}

void Camera::UpdateCameraViewMatrix()
{
    GetTransform();

    vec3 euler = transform->GetEulerAngle();
    forward.x = cos(euler.x) * cos(euler.y);
    forward.y = sin(euler.y);
    forward.z = cos(euler.x) * sin(euler.y);

    forward = glm::normalize(forward);
    right = glm::cross(forward, worldUp);
    up = glm::cross(forward, right);

    viewMatrix = glm::lookAt(transform->GetPosition(), transform->GetPosition() + forward, up);
}

Transform *Camera::GetTransform()
{
    if (!transform)
    {
        transform = dynamic_cast<Transform *>(gameObject->GetComponent("Transform"));
    }
}

void Camera::SetFOV(float fov) { this->fieldOfView = fov; }
void Camera::SetRatio(float ratio) { this->ratio = ratio; }
void Camera::SetNearClipping(float clipping) { this->nearClipping = clipping; }
void Camera::SetFarClipping(float clipping) { this->farClipping = clipping; }
void Camera::SetPosition(vec3 position)
{
    GetTransform()->SetPosition(position);
    UpdateCameraViewMatrix();
}

Camera::~Camera()
{
}