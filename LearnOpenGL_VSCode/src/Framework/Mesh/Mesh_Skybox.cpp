#include "Mesh_Skybox.h"

Mesh_Skybox::Mesh_Skybox()
{

    verticesList.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, -0.5f, 0.5f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.5f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, -0.5f, -0.5f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, 0.5f, -0.5f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, -0.5f, 0.5f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, -0.5f, -0.5f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, 0.5f, -0.5f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.5f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.5f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, 0.5f, -0.5f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, -0.5f, -0.5f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, -0.5f, 0.5f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f)));

    indicesList.insert(indicesList.end(), {0, 2, 1, // front fac
                                              0, 3, 2,

                                              4, 6, 5, // back face
                                              4, 7, 6,

                                              8, 10, 9, // right face
                                              8, 11, 10,

                                              12, 14, 13, // left face
                                              12, 15, 14,

                                              16, 18, 17, // top face
                                              16, 19, 18,

                                              20, 22, 21, // bottom face
                                              20, 23, 22});
}

Mesh_Skybox::~Mesh_Skybox() {}