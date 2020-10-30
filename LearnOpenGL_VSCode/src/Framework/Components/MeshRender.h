#pragma once

#include "Component.h"
#include "../Mesh/Mesh.h"
#include "../Shaders/Shader.h"
#include "Transform.h"
#include "Camera.h"

class MeshRender : public Component
{
public:
    MeshRender(string vertex, string frag);
    MeshRender();
    virtual void Update();
    void SetMesh(Mesh *);
    Shader &GetShader();
    ~MeshRender();

private:
    Mesh *mesh = nullptr;
    Transform *transform = nullptr;
    Camera *camera = nullptr;
    unsigned int VBO = 0, VAO = 0, EBO = 0;
    Shader shader;
};
