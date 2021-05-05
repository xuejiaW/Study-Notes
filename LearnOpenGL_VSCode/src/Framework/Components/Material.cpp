#include "Material.h"
#include "../Debug.h"
#include <algorithm>

Material::Material() : Material("../Framework/Shaders/Default.vs", "../Framework/Shaders/Default.fs")
{
}

Material::Material(Shader *shader)
{
    this->shader = shader;
}

Material::Material(string vertexPath, string fragPath) : Material(new Shader(vertexPath.c_str(), fragPath.c_str())) {}

void Material::AddTexture(string target, Texture *texture)
{
    targetList.push_back(target);

    textureList.push_back(texture);
}

void Material::RemoveTexture(unsigned int textureId)
{
    vector<Texture *>::iterator texIt = std::find_if(textureList.begin(), textureList.end(), [textureId](Texture *tex) { return tex->GetID() == textureId; });

    if (texIt != textureList.end())
        textureList.erase(texIt);
}

void Material::UdpateTexture()
{
    for (int i = 0; i != GetTextureCount(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        textureList[i]->BindTexture();
        shader->SetInt(targetList[i], i);
    }
}

void Material::SetColor(vec3 color)
{
    baseColor = color;
    shader->SetVec3("baseColor", color);
}

vec3 Material::GetColor() { return baseColor; }

unsigned int Material::GetTextureCount()
{
    return textureList.size();
}

int Material::GetTexture(int index)
{
    if (index >= textureList.size())
        return -1;
    return textureList[index]->GetID();
}

Shader *Material::GetShader()
{
    return shader;
}

Material::~Material() {}