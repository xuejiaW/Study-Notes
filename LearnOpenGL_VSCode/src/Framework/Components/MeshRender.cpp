#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "MeshRender.h"
#include "Texture.h"
#include "../Scene.h"

using std::cout;
using std::endl;

MeshRender::MeshRender(Shader *shader)
{
    name = "MeshRender";
    this->shader = shader;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
}

MeshRender::MeshRender() : MeshRender(new Shader("../Framework/Shaders/Default.vertex", "../Framework/Shaders/Default.fragment"))
{
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Shader *MeshRender::GetShader()
{
    return shader;
}

void MeshRender::Update()
{
    if (!transform)
        transform = gameObject->GetTransform();

    if (!camera)
        camera = Scene::GetInstance()->GetMainCamera();

    if (!transform || !camera)
    {
        cout << "Lack of Transform or Camera" << endl;
        return;
    }

    shader->Use();

    glm::mat4 model, xRot, yRot, zRot;
    model = glm::translate(model, transform->GetPosition());
    xRot = glm::rotate(xRot, transform->GetEulerAngle().x, glm::vec3(1, 0, 0));
    yRot = glm::rotate(yRot, transform->GetEulerAngle().y, glm::vec3(0, 1, 0));
    zRot = glm::rotate(zRot, transform->GetEulerAngle().z, glm::vec3(0, 0, 1));
    model *= yRot;
    model *= zRot;
    model *= zRot;
    model = glm::scale(model, transform->GetScale());

    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = camera->GetProjectionMatrix();

    glUniformMatrix4fv(glGetUniformLocation(shader->Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    if (Component *com = gameObject->GetComponent("Texture"))
    {
        Texture *texture = dynamic_cast<Texture *>(com);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->GetID());
        glUniform1i(glGetUniformLocation(shader->Program, "outTexture"), 0);
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, mesh->GetVertexNum(), GL_UNSIGNED_INT, 0);
}

MeshRender::~MeshRender()
{
}