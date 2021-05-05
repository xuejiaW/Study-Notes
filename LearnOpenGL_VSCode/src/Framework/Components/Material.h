#include "Component.h"
#include "Texture.h"
#include "Cubemap.h"
#include "../Shaders/Shader.h"

#include <vector>
#include <string>

using std::vector;

class Material
{
public:
    Material();
    Material(Shader *shader);
    Material(string vertexPath, string fragPath);

    void SetColor(vec3 color);
    vec3 GetColor();
    void AddTexture(string target, Texture *texture);
    void UdpateTexture();
    void RemoveTexture(unsigned int textureId);
    unsigned int GetTextureCount();
    int GetTexture(int index);
    Shader *GetShader();
    ~Material();

private:
    vec3 baseColor;
    Shader *shader = nullptr;
    vector<Texture *> textureList;
    vector<string> targetList;
};
