#pragma once

#include "Component.h"
#include "../Mesh/Mesh.h"
#include "../Shaders/Shader.h"
#include "Transform.h"
#include "Camera.h"

class MeshRender : public Component
{
public:
    MeshRender(Shader* shader);
    MeshRender();
    virtual void Update();
    void SetMesh(Mesh *);
    Shader *GetShader();
    ~MeshRender();

private:
    unsigned int VBO = 0, VAO = 0, EBO = 0;
    Mesh *mesh = nullptr;
    Transform *transform = nullptr;
    Camera *camera = nullptr;
    Shader *shader = nullptr;
};
