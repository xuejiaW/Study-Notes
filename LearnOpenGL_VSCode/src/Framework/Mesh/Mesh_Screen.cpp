#include "./Mesh_Screen.h"

Mesh_Screen::Mesh_Screen(/* args */)
{
    vertices = new float[32]{
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // front face
        1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

    indices = new unsigned int[6]{
        0, 1, 2,
        0, 2, 3};

    singleDataSize = 8;
    vertexNum = 6;
    dataSize_byte = 32 * sizeof(float);
    indicesSize_byte = 6 * sizeof(unsigned int);
}

Mesh_Screen::~Mesh_Screen()
{
}