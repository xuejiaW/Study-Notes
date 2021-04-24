#pragma once

#include <vector>
#include "../Data/Vertex.h"

class Mesh
{
public:
    std::vector<Vertex> verticesList;
    std::vector<unsigned int> indicesList;

    Mesh();
    Mesh(std::vector<Vertex> verticesList, std::vector<unsigned int> indicesList);
    virtual ~Mesh();

protected:
};
