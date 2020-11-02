#include <algorithm>
#include <iostream>
#include "../Scene.h"
#include "GameObject.h"
#include "../Components/Component.h"
#include "../Components/Transform.h"
#include "../Components/MeshRender.h"

GameObject::GameObject()
{
    componentsList = vector<Component *>();
    childrenList = vector<GameObject *>();
    scene = Scene::GetInstance();
}

void GameObject::AddComponent(Component *component)
{
    component->SetAttachGameObject(this);
    componentsList.push_back(component);
}

Component *GameObject::GetComponent(std::string name)
{
    vector<Component *>::iterator resultIterator = std::find_if(componentsList.begin(), componentsList.end(),
                                                                [name](const Component *component) { return component->name == name; });
    if (resultIterator != componentsList.end())
        return *resultIterator;

    return nullptr;
}

Transform *GameObject::GetTransform()
{
    if (!transform)
    {
        Component *transCom = GetComponent("Transform");
        if (transCom)
            transform = dynamic_cast<Transform *>(transCom);
    }

    return transform ? transform : nullptr;
}

MeshRender *GameObject::GetMeshRender()
{
    if (!meshRender)
    {
        Component *meshRenderCom = GetComponent("MeshRender");
        if (meshRenderCom)
            meshRender = dynamic_cast<MeshRender *>(meshRenderCom);
    }

    return meshRender ? meshRender : nullptr;
}

void GameObject::Update()
{
    for (GameObject *const &go : childrenList)
        go->Update();

    for (Component *const &component : componentsList)
        component->Update();

    if (updateOperation)
        updateOperation();
}

GameObject::~GameObject()
{
}