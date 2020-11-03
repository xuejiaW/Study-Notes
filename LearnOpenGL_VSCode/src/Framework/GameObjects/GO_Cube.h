#pragma once

#include "GameObject.h"
#include "../Components/Transform.h"
#include "../Components/MeshRender.h"
#include "../Components/Texture.h"

class GO_Cube : public GameObject
{
public:
    GO_Cube(MeshRender* meshRender);
    GO_Cube();
    ~GO_Cube();

private:
    Transform *transform = nullptr;
    MeshRender *meshRender = nullptr;
};
