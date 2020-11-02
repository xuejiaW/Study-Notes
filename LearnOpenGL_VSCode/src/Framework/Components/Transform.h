#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include "Component.h"
using namespace glm;

class Transform : public Component
{
public:
    Transform(/* args */);
    virtual void Update();

    void SetPosition(vec3 position);
    void SetEulerAngle(vec3 eulerAngle);
    void SetScale(vec3 scale);
    void RotateAround(vec3 position, vec3 axis, float angle);

    vec3 GetPosition();
    vec3 GetEulerAngle();
    vec3 GetScale();
    ~Transform();

private:
    vec3 position;
    vec3 eulerAngle;
    vec3 scale;
};
