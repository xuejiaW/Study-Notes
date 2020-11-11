#include "Component.h"
#include "Texture.h"
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
    void AddTexture(string target, Texture *texture);
    void AddTexture(string target, int tID);
    void UdpateTexture();
    void RemoveTexture(unsigned int textureId);
    unsigned int GetTextureCount();
    int GetTexture(int index);
    Shader *GetShader();
    ~Material();

private:
    Shader *shader = nullptr;
    vector<unsigned int> textureIDList;
    vector<string> targetList;
};
