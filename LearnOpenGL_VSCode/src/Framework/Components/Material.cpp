#include "Material.h"
#include <algorithm>

Material::Material()
{
}

Material::Material(Shader *shader) : Material()
{
    this->shader = shader;
}

Material::Material(string vertexPath, string fragPath) : Material(new Shader(vertexPath.c_str(), fragPath.c_str())) {}

void Material::AddTexture(Texture *texture)
{
    textureList.push_back(texture);
}
void Material::RemoveTexture(unsigned int textureId)
{
    vector<Texture *>::iterator it = std::find_if(textureList.begin(), textureList.end(),
                                                  [textureId](const Texture *texture) { return texture->GetID() == textureId; });
    if (it != textureList.end())
        textureList.erase(it);
}

Material::~Material()
{
}