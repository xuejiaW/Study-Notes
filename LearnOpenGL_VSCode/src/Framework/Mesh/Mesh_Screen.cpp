#include "./Mesh_Screen.h"

Mesh_Screen::Mesh_Screen(/* args */)
{
    verticesList.push_back(Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f))); // front face
    verticesList.push_back(Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    verticesList.push_back(Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    verticesList.push_back(Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0)));

    indicesList.insert(indicesList.end(), {0, 1, 2, 0, 2, 3});
}

Mesh_Screen::~Mesh_Screen()
{
}