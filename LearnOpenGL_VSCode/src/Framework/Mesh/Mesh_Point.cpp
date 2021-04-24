#include "Mesh_Point.h"

Mesh_Point::Mesh_Point()
{
    verticesList.push_back(Vertex(glm::vec3(0.0f,0.0f,0.0f)));
    indicesList.push_back(0);
}

Mesh_Point::~Mesh_Point() {}