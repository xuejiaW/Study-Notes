#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Component;
class Transform;
class Scene;

class GameObject
{
public:
    string name;
    GameObject();

    void AddComponent(Component *component);
    Component *GetComponent(string name);
    Transform *GetTransform();
    virtual void Update();

    ~GameObject();

protected:
    Scene *scene = nullptr;

private:
    Transform *transform = nullptr;
    vector<GameObject *> childrenList;
    vector<Component *> componentsList;
};
