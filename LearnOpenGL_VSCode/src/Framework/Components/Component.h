#pragma once

#include <string>
#include "../GameObjects/GameObject.h"


class Component
{
public:
    std::string name;
    GameObject *gameObject;
    Component(/* args */);
    virtual void SetAttachGameObject(GameObject *attachedGO);
    virtual void Update();
    ~Component();
};
