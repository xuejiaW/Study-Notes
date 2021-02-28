#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture() {}

Texture::Texture(string texturePath, bool sRGB)
{
    int nrChannels = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

    GLuint texType = sRGB ? (nrChannels == 3 ? GL_SRGB : GL_SRGB_ALPHA) : (nrChannels == 3 ? GL_RGB : GL_RGBA);
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, texType, width, height, 0, nrChannels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(unsigned int tid, int width, int height)
{
    this->id = tid;
    this->width = width;
    this->height = height;
}

unsigned int Texture::GetID() { return id; }
unsigned int Texture::GetID() const { return id; }
int Texture::GetWidth() { return width; }
int Texture::GetHeight() { return height; }

void Texture::SetWrap(int wrap_S, int wrap_T)
{
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_T);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::BindTexture()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

Texture::~Texture()
{
    glDeleteTextures(1, &id);
}