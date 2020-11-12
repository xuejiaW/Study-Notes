#include "Material.h"
#include "../Debug.h"
#include <algorithm>

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
    targetList.push_back(target);
    textureIDList.push_back(texture->GetID());
}

void Material::AddTexture(string target, int tID)
{
    targetList.push_back(target);
    textureIDList.push_back(tID);
}

void Material::RemoveTexture(unsigned int textureId)
{
    vector<unsigned int>::iterator it = std::find_if(textureIDList.begin(), textureIDList.end(),
                                                     [textureId](unsigned int tid) { return tid == textureId; });
    if (it != textureIDList.end())
        textureIDList.erase(it);
}

void Material::UdpateTexture()
{
    for (int i = 0; i != GetTextureCount(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textureIDList[i]);
        shader->SetInt(targetList[i], i);
    }
}

void Material::SetColor(vec3 color)
{
    shader->SetVec3("baseColor", color);
}

unsigned int Material::GetTextureCount()
{
    return textureIDList.size();
}

int Material::GetTexture(int index)
{
    if (index >= textureIDList.size())
        return -1;
    return textureIDList[index];
}

Shader *Material::GetShader()
{
    return shader;
}

Material::~Material() {}