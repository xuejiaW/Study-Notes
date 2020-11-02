#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Component;
class Transform;
class MeshRender;
class Scene;

class GameObject
{
public:
    string name;
    GameObject();

    void AddComponent(Component *component);
    Component *GetComponent(string name);
    Transform *GetTransform();
    MeshRender *GetMeshRender();
    void (*updateOperation)() = nullptr;
    virtual void Update();
    ~GameObject();

protected:
    Scene *scene = nullptr;

private:
    MeshRender *meshRender = nullptr;
    Transform *transform = nullptr;
    vector<GameObject *> childrenList;
    vector<Component *> componentsList;
};
