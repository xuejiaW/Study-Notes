#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Component.h"
#include "Material.h"
#include "../Mesh/Mesh.h"
#include "../Shaders/Shader.h"
#include "Transform.h"
#include "Camera.h"

class MeshRender : public Component
{
public:
    MeshRender(Material *material, bool usingSharedCamera = false);
    MeshRender(Shader *shader, bool usingSharedCamera = false);
    MeshRender();

    virtual void Update();
    void SetPreRenderHandle(void (*)());
    void SetPostRenderHandle(void (*)());
    void SetLoadingBufferHandle(void (*)());
    void SetInstancingCount(int count);
    void SetMesh(Mesh *);
    void DrawMesh();
    void SetDrawingMode(unsigned int mode);

    Shader *GetShader();
    Material *GetMaterial();

    ~MeshRender();

private:
    static bool uboDataCreated; // Ensure that the UBO only created once
    static bool uboDataUpdated; // Ensure that the UBO only updated once
    bool usingSharedCameraState = false;
    unsigned int drawingMode = GL_TRIANGLES;
    unsigned int VBO = 0, VAO = 0, EBO = 0, UBO = 0;
    void (*loadingBufferData)() = nullptr;
    void (*preRenderHandle)() = nullptr;
    void (*postRenderHandle)() = nullptr;
    Mesh *mesh = nullptr;
    Transform *transform = nullptr;
    Camera *camera = nullptr;
    Material *material = nullptr;

    int instancingCount = 0;
};
