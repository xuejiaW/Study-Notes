#pragma once

#include "GameObject.h"
#include "../Components/Transform.h"
#include "../Components/MeshRender.h"
#include "../Components/Texture.h"

class GO_Point : public GameObject
{
public:
    GO_Point(MeshRender *meshRender);
    GO_Point();
    ~GO_Point();

private:
    Transform *transform = nullptr;
    MeshRender *meshRender = nullptr;
};
