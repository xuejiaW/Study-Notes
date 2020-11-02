#pragma once

#include <string>
#include "../Debug.h"
#include "../GameObjects/GameObject.h"

class Component
{
public:
    std::string name;
    GameObject *gameObject;
    Component();
    virtual void SetAttachGameObject(GameObject *attachedGO);
    virtual void Update();
    ~Component();
};
