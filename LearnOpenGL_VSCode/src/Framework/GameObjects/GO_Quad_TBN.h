#pragma once

#include "GameObject.h"
#include "../Components/Transform.h"
#include "../Components/MeshRender.h"
#include "../Components/Texture.h"

class GO_Quad_TBN : public GameObject
{
public:
    GO_Quad_TBN(MeshRender* meshRender);
    GO_Quad_TBN();
    ~GO_Quad_TBN();

private:
    Transform *transform = nullptr;
    MeshRender *meshRender = nullptr;
};