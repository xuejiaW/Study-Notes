#pragma once

#include <string>
#include "../GameObjects/GameObject.h"


class Component
{
public:
    std::string name;
    GameObject *gameObject;
    Component(/* args */);
    void SetAttachGameObject(GameObject *attachedGO);
    virtual void Update();
    ~Component();
};
