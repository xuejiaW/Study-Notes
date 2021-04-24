#include "Mesh_Cube.h"

Mesh_Cube::Mesh_Cube() : Mesh()
{
    // Front Face
    verticesList.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)));

    // Back Face
    verticesList.push_back(Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)));

    // Right Face
    verticesList.push_back(Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)));

    // Left Face
    verticesList.push_back(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)));

    // Top Face
    verticesList.push_back(Vertex(glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

    // Bottom Face
    verticesList.push_back(Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f))); // bottom face
    verticesList.push_back(Vertex(glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    verticesList.push_back(Vertex(glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    verticesList.push_back(Vertex(glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

    indicesList = std::vector<unsigned int>{
            0, 1, 2, // front face
            0, 2, 3,
    
            4, 5, 6, // back face
            4, 6, 7,
    
            8, 9, 10, // right face
            8, 10, 11,
    
            12, 13, 14, // left face
            12, 14, 15,
    
            16, 17, 18, // top face
            16, 18, 19,
    
            20, 21, 22, // bottom face
            20, 22, 23};
}

Mesh_Cube::~Mesh_Cube() {}