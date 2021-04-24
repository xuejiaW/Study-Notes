#include <iostream>
#include "MeshRender.h"
#include "Texture.h"
#include "../Scene.h"
#include "../Utils.h"

using std::cout;
using std::endl;

bool MeshRender::uboDataCreated = false;
bool MeshRender::uboDataUpdated = false;

MeshRender::MeshRender(Shader *shader, bool usingSharedState) : MeshRender(new Material(shader), usingSharedState) {}

MeshRender::MeshRender() : MeshRender(new Shader("../Framework/Shaders/Default.vs", "../Framework/Shaders/Default.fs"), false) {}

MeshRender::MeshRender(Material *material, bool usingSharedState) : Component(), usingSharedCameraState(usingSharedState)
{
    if (usingSharedCameraState)
        Debug::Log("Shared");
    else
        Debug::Log("Not shared");

    name = "MeshRender";
    this->material = material;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    if (usingSharedCameraState)
    {
        if (!uboDataCreated)
        {
            glGenBuffers(1, &UBO);
            glBindBuffer(GL_UNIFORM_BUFFER, UBO);
            glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(mat4), nullptr, GL_STATIC_DRAW);
            glBindBufferBase(GL_UNIFORM_BUFFER, 0, UBO); // bind to 0 binding point
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
            uboDataCreated = true;

            Scene::GetInstance()->preRender = []() {
                uboDataUpdated = false;
            };
        }

        uint uniformBlockIndex = glGetUniformBlockIndex(this->material->GetShader()->Program, "Matrices");
        glUniformBlockBinding(this->material->GetShader()->Program, uniformBlockIndex, 0); // Binding to Binding Point 0
    }
}

void MeshRender::SetMesh(Mesh *mesh)
{
    this->mesh = mesh;
    GetShader()->Use();
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->mesh->verticesList.size() * sizeof(Vertex), &this->mesh->verticesList[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->mesh->indicesList.size() * sizeof(unsigned int), &this->mesh->indicesList[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, TexCoord)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Tangent));
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Bitangent));
    glEnableVertexAttribArray(4);

    if (loadingBufferData)
        loadingBufferData();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Shader *MeshRender::GetShader()
{
    return material->GetShader();
}

void MeshRender::SwitchMaterial(Material *material)
{
    this->material = material;
}

Material *MeshRender::GetMaterial()
{
    return material;
}

void MeshRender::Update()
{
    if (!transform)
        transform = gameObject->GetTransform();

    if (!camera)
        camera = Scene::GetInstance()->GetMainCamera();

    if (preRenderHandle)
        preRenderHandle();

    Shader *shader = material->GetShader();
    shader->Use();

    if (transform)
    {
        glm::mat4 model = GetModelMatrix(transform);
        shader->SetMat4("model", model);
    }

    if (camera && !Scene::GetInstance()->renderingDepthMap)
    {
        glm::mat4 view = camera->GetViewMatrix();
        glm::mat4 projection = camera->GetProjectionMatrix();

        if (!usingSharedCameraState)
        {
            shader->SetMat4("view", view);
            shader->SetMat4("projection", projection);
        }
        else
        {
            if (!uboDataUpdated) // only need to update UBO once in every frame
            {
                glBindBuffer(GL_UNIFORM_BUFFER, UBO);
                glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), glm::value_ptr(projection));
                glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), glm::value_ptr(view));
                glBindBuffer(GL_UNIFORM_BUFFER, 0);
            }
        }
    }

    DrawMesh();

    if (postRenderHandle)
        postRenderHandle();
}

void MeshRender::SetInstancingCount(int count)
{
    this->instancingCount = count;
}

void MeshRender::DrawMesh()
{
    glBindVertexArray(VAO);
    material->UdpateTexture();

    if (instancingCount == 0)
        glDrawElements(drawingMode, mesh->indicesList.size(), GL_UNSIGNED_INT, 0);
    else
    {
        glDrawElementsInstanced(drawingMode, mesh->indicesList.size(), GL_UNSIGNED_INT, 0, instancingCount);
    }

    glBindVertexArray(0);
}

void MeshRender::SetDrawingMode(unsigned int mode)
{
    drawingMode = mode;
}

void MeshRender::SetPreRenderHandle(void (*preRenderHandle)())
{
    this->preRenderHandle = preRenderHandle;
}
void MeshRender::SetPostRenderHandle(void (*postRenderHandle)())
{
    this->postRenderHandle = postRenderHandle;
}

void MeshRender::SetLoadingBufferHandle(void (*loadBuffer)())
{
    this->loadingBufferData = loadBuffer;
}

MeshRender::~MeshRender() {}