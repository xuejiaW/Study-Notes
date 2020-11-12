#include "Mesh_Skybox.h"

Mesh_Skybox::Mesh_Skybox()
{
    vertices = new float[80]{
        -0.5f, -0.5f, 0.5f, // front face
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        0.5f, -0.5f, -0.5f, // back face
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,

        0.5f, -0.5f, 0.5f, // right face
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,

        -0.5f, -0.5f, -0.5f, // left face
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,

        -0.5f, 0.5f, 0.5f, // top face
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,

        -0.5f, -0.5f, -0.5f, // bottom face
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f};

    indices = new unsigned int[36]{
        0, 2, 1, // front fac
        0, 3, 2,

        4, 6, 5, // back face
        4, 7, 6,

        8, 10, 9, // right face
        8, 11, 10,

        12, 14, 13, // left face
        12, 15, 14,

        16, 18, 17, // top face
        16, 19, 18,

        20, 22, 21, // bottom face
        20, 23, 22};

    singleDataSize = 3;
    vertexNum = 36;
    dataSize_byte = 72 * sizeof(float);
    indicesSize_byte = 36 * sizeof(unsigned int);
}

Mesh_Skybox::~Mesh_Skybox(){}