#include "Mesh.h"

Mesh::Mesh() {}
unsigned int Mesh::GetDataSize() { return dataSize_byte; }
unsigned int Mesh::GetIndicesSize() { return indicesSize_byte; }
unsigned int Mesh::GetVertexNum() { return vertexNum; }
Mesh::~Mesh()
{
    if (vertices)
        delete vertices;
    if (indices)
        delete indices;
}