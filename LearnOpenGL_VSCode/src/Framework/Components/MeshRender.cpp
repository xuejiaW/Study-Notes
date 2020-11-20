#include <iostream>
#include "MeshRender.h"
#include "Texture.h"
#include "../Scene.h"

using std::cout;
using std::endl;

bool MeshRender::uboDataCreated = false;
bool MeshRender::uboDataUpdated = false;

MeshRender::MeshRender(Shader *shader, bool usingSharedState) : MeshRender(new Material(shader), usingSharedState) {}

MeshRender::MeshRender() : MeshRender(new Shader("../Framework/Shaders/Default.vertex", "../Framework/Shaders/Default.fragment"), false) {}

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
    glBufferData(GL_ARRAY_BUFFER, this->mesh->GetDataSize(), this->mesh->vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->mesh->GetIndicesSize(), this->mesh->indices, GL_STATIC_DRAW);

    unsigned int singleDataSize = this->mesh->GetSingleDataSize();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, singleDataSize * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    if (singleDataSize >= 3)
    {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, singleDataSize * sizeof(float), (void *)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
    if (singleDataSize >= 5)
    {
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, singleDataSize * sizeof(float), (void *)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Shader *MeshRender::GetShader()
{
    return material->GetShader();
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

    material->GetShader()->Use();
    GLuint shaderProgram = material->GetShader()->Program;

    if (transform && camera)
    {
        glm::mat4 model, xRot, yRot, zRot;
        model = glm::translate(model, transform->GetPosition());
        xRot = glm::rotate(xRot, glm::radians(transform->GetEulerAngle().x), glm::vec3(1, 0, 0));
        yRot = glm::rotate(yRot, glm::radians(transform->GetEulerAngle().y), glm::vec3(0, 1, 0));
        zRot = glm::rotate(zRot, glm::radians(transform->GetEulerAngle().z), glm::vec3(0, 0, 1));
        model *= yRot;
        model *= xRot;
        model *= zRot;
        model = glm::scale(model, transform->GetScale());

        glm::mat4 view = camera->GetViewMatrix();
        glm::mat4 projection = camera->GetProjectionMatrix();

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

        if (!usingSharedCameraState)
        {
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        }
        else
        {
            if (!uboDataUpdated)
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


void MeshRender::DrawMesh()
{
    glBindVertexArray(VAO);
    material->UdpateTexture();
    glDrawElements(drawingMode, mesh->GetVertexNum(), GL_UNSIGNED_INT, 0);
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

MeshRender::~MeshRender() {}