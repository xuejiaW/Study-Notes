#include "Component.h"

Component::Component(/* args */)
{
}

void Component::SetAttachGameObject(GameObject *attachGO)
{
    this->gameObject = attachGO;
}

void Component::Update() {}

Component::~Component() { }