#include "Transform.h"

Transform::Transform()
{
    name = "Transform";
    position = vec3(0, 0, 0);
    eulerAngle = vec3(0, 0, 0);
    scale = vec3(0.5f, 0.5f, 0.5f);
}

void Transform::Update() {}

void Transform::SetPosition(vec3 position) { this->position = position; }

void Transform::SetEulerAngle(vec3 eulerAngle) { this->eulerAngle = eulerAngle; }

void Transform::SetScale(vec3 scale) { this->scale = scale; }

vec3 Transform::GetPosition() { return position; }

vec3 Transform::GetEulerAngle() { return eulerAngle; }

vec3 Transform::GetScale() { return scale; }

void Transform::RotateAround(vec3 anchor, vec3 axis, float angle)
{
    glm::mat4 model;
    vec3 inverseAnchor = anchor;
    anchor[0] *= -1;
    anchor[1] *= -1;
    anchor[2] *= -1;

    model = glm::translate(model, inverseAnchor);
    model = glm::rotate(model, angle, axis);
    model = glm::translate(model, anchor);

    position = model * vec4(position, 1);
}

Transform::~Transform() {}