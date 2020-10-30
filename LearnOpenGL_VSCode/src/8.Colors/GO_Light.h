#pragma once

#include "../Framework/GameObjects/GameObject.h"
#include "../Framework/Components/MeshRender.h"
#include "../Framework/Components/Transform.h"

class GO_Light : public GameObject
{
public:
    GO_Light();
    ~GO_Light();

private:
    Transform *transform = nullptr;
    MeshRender *meshRender = nullptr;
};
