#pragma once

#include "GameObject.h"
#include "../Components/Transform.h"
#include "../Components/MeshRender.h"
#include "../Components/Texture.h"

class GO_InverseCube : public GameObject
{
public:
    GO_InverseCube(MeshRender* meshRender);
    GO_InverseCube();
    ~GO_InverseCube();

private:
    Transform *transform = nullptr;
    MeshRender *meshRender = nullptr;
};
