#pragma once

class Mesh
{
public:
    float *vertices;
    unsigned int *indices;

    Mesh();
    unsigned int GetDataSize();
    unsigned int GetIndicesSize();
    unsigned int GetVertexNum();
    virtual ~Mesh();

protected:
    unsigned int vertexNum;
    unsigned int dataSize_byte;
    unsigned int indicesSize_byte;
};
