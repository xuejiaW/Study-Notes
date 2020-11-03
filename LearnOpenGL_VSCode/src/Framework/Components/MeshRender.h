#pragma once

#include "Component.h"
#include "Material.h"
#include "../Mesh/Mesh.h"
#include "../Shaders/Shader.h"
#include "Transform.h"
#include "Camera.h"

class MeshRender : public Component
{
public:
    MeshRender(Material *material);
    MeshRender(Shader *shader);
    MeshRender();
    virtual void Update();
    void SetMesh(Mesh *);

    Shader *GetShader();
    Material *GetMaterial();

    ~MeshRender();

private:
    unsigned int VBO = 0, VAO = 0, EBO = 0;
    Mesh *mesh = nullptr;
    Transform *transform = nullptr;
    Camera *camera = nullptr;
    Material *material = nullptr;
};
