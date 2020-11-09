#include "Material.h"
#include "../Debug.h"
#include <algorithm>

// vector<Texture *> Material::textureList = vector<Texture *>();

Material::Material() : Material("../Framework/Shaders/Default.vertex", "../Framework/Shaders/Default.fragment")
{
}

Material::Material(Shader *shader)
{
    this->shader = shader;
}

Material::Material(string vertexPath, string fragPath) : Material(new Shader(vertexPath.c_str(), fragPath.c_str())) {}

void Material::AddTexture(string target, Texture *texture)
{
    // glActiveTexture(GL_TEXTURE0 + GetTextureCount());
    // glBindTexture(GL_TEXTURE_2D, texture->GetID());
    // shader->SetInt(target, GetTextureCount());
    targetList.push_back(target);
    textureList.push_back(texture);
}

void Material::RemoveTexture(unsigned int textureId)
{
    vector<Texture *>::iterator it = std::find_if(textureList.begin(), textureList.end(),
                                                  [textureId](const Texture *texture) { return texture->GetID() == textureId; });
    if (it != textureList.end())
        textureList.erase(it);
}

void Material::UdpateTexture()
{
    for (int i = 0; i != GetTextureCount(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textureList[i]->GetID());
        shader->SetInt(targetList[i], i);
    }
}

void Material::SetColor(vec3 color)
{
    shader->SetVec3("baseColor", color);
}

unsigned int Material::GetTextureCount()
{
    return textureList.size();
}

Texture *Material::GetTexture(int index)
{
    if (index >= textureList.size())
        return nullptr;
    return textureList[index];
}

Shader *Material::GetShader()
{
    return shader;
}

Material::~Material() {}