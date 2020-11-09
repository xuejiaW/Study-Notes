
#pragma once

#include "GameObject.h"
#include "../Components/Transform.h"
#include "../Components/MeshRender.h"
#include "../Components/Texture.h"

class GO_Plane : public GameObject
{
public:
    GO_Plane(MeshRender* meshRender);
    GO_Plane();
    ~GO_Plane();

private:
    Transform *transform = nullptr;
    MeshRender *meshRender = nullptr;
};