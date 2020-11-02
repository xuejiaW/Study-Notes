#include "Mesh.h"

Mesh::Mesh() : singleDataSize(0), vertexNum(0), dataSize_byte(0), indicesSize_byte(0) {}

unsigned int Mesh::GetDataSize() { return dataSize_byte; }
unsigned int Mesh::GetIndicesSize() { return indicesSize_byte; }
unsigned int Mesh::GetVertexNum() { return vertexNum; }
unsigned int Mesh::GetSingleDataSize() { return singleDataSize; }

Mesh::~Mesh()
{
    if (vertices)
        delete vertices;
    if (indices)
        delete indices;
}