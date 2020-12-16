#ifndef UTILS
#define UTILS

#include "./Components/Transform.h"

mat4 GetModelMatrix(Transform *transform)
{
    glm::mat4 model, xRot, yRot, zRot;
    model = glm::translate(model, transform->GetPosition());
    xRot = glm::rotate(xRot, glm::radians(transform->GetEulerAngle().x), glm::vec3(1, 0, 0));
    yRot = glm::rotate(yRot, glm::radians(transform->GetEulerAngle().y), glm::vec3(0, 1, 0));
    zRot = glm::rotate(zRot, glm::radians(transform->GetEulerAngle().z), glm::vec3(0, 0, 1));
    model *= yRot;
    model *= xRot;
    model *= zRot;
    model = glm::scale(model, transform->GetScale());
    return model;
}
#endif
