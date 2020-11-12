#pragma once

#include "../Shaders/Shader.h"
#include "../Mesh/Mesh_Skybox.h"
#include "../Mesh/Mesh_Cube.h"
#include "Cubemap.h"
#include "../GameObjects/GameObject.h"
#include "Camera.h"

class Skybox : public GameObject
{
public:
    Skybox(Cubemap *cubemap);
    virtual void Update();
    void (*preRender)() = nullptr;
    void (*postRender)() = nullptr;
    ~Skybox();

private:
    unsigned int VBO = 0, VAO = 0, EBO = 0;
    Cubemap *cubemap = nullptr;
    Shader *skyboxShader = nullptr;
    Mesh *mesh = nullptr;
    Camera *camera = nullptr;

    void SetSkyboxMesh(Mesh *mesh);
};
