#include "Cubemap.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#endif

Cubemap::Cubemap(vector<string> facesSource)
{
    this->faceSources = facesSource;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    int nrChannels = 0;
    unsigned char *data = nullptr;
    for (unsigned int i = 0; i != facesSource.size(); ++i)
    {
        data = stbi_load(faceSources[i].c_str(), &width, &height, &nrChannels, 0);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, nrChannels == 3 ? GL_RGB : GL_RGBA,
                     width, height, 0, nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

Cubemap::Cubemap(int id)
{
    this->id = id;
}

unsigned int Cubemap::GetID()
{
    return id;
}

unsigned int Cubemap::GetID() const
{
    return id;
}

int Cubemap::GetWidth()
{
    return width;
}

int Cubemap::GetHeight()
{
    return height;
}

void Cubemap::SetWrap(int wrap_S, int wrap_T, int wrap_R)
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrap_S);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrap_T);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, wrap_R);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Cubemap::BindTexture()
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}

Cubemap::~Cubemap() {}