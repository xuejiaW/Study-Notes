#include "Mesh_Point.h"

Mesh_Point::Mesh_Point()
{
    vertices = new float[3]{
        0.0f, 0.0f, 0.0f};
    indices = new unsigned int[1]{0};
    singleDataSize = 3;
    vertexNum = 1;
    dataSize_byte = 3 * sizeof(float);
    indicesSize_byte = sizeof(unsigned int);
}

Mesh_Point::~Mesh_Point() {}