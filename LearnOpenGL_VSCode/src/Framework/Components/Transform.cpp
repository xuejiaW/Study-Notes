#include "Transform.h"

Transform::Transform()
{
    name = "Transform";
    position = vec3(0, 0, 0);
    eulerAngle = vec3(30, 50, 60);
    scale = vec3(0.5f, 0.5f, 0.5f);
}

void Transform::Update()
{
}

void Transform::SetPosition(vec3 position) { this->position = position; }

void Transform::SetEulerAngle(vec3 eulerAngle) { this->eulerAngle = eulerAngle; }

void Transform::SetScale(vec3 scale) { this->scale = scale; }

vec3 Transform::GetPosition() { return position; }

vec3 Transform::GetEulerAngle() { return eulerAngle; }

vec3 Transform::GetScale() { return scale; }

Transform::~Transform() {}