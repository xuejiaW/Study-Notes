#include "Mesh.h"

Mesh::Mesh() : verticesList(std::vector<Vertex>()), indicesList(std::vector<unsigned int>()) { }

Mesh::Mesh(std::vector<Vertex> verticesList, std::vector<unsigned int> indicesList)
{
    this->verticesList = verticesList;
    this->indicesList = indicesList;
}

Mesh::~Mesh() { }