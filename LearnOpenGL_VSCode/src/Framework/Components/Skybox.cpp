#include "Skybox.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Scene.h"

Skybox::Skybox(Cubemap *cubemap)
{
    this->cubemap = cubemap;
    skyboxShader = new Shader("../Framework/Shaders/Skybox.vert", "../Framework/Shaders/Skybox.frag");

    SetSkyboxMesh(new Mesh_Skybox());
}

void Skybox::SetSkyboxMesh(Mesh *mesh)
{
    this->mesh = mesh;

    skyboxShader->Use();

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->mesh->GetDataSize(), this->mesh->vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->mesh->GetIndicesSize(), this->mesh->indices, GL_STATIC_DRAW);

    unsigned int singleDataSize = this->mesh->GetSingleDataSize();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, singleDataSize * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Skybox::Update()
{
    if (!camera)
        camera = Scene::GetInstance()->GetMainCamera();

    if (preRender)
        preRender();

    skyboxShader->Use();

    if (camera)
    {
        glm::mat4 view = glm::mat4(glm::mat3(camera->GetViewMatrix()));
        glm::mat4 projection = camera->GetProjectionMatrix();
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(skyboxShader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    }

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->GetID());

    glDrawElements(GL_TRIANGLES, mesh->GetVertexNum(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    if (postRender)
        postRender();
}

Skybox::~Skybox() {}