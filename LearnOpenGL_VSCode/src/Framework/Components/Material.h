#include "Component.h"
#include "Texture.h"
#include "../Shaders/Shader.h"

#include <vector>
#include <string>

using std::vector;

class Material : public Component
{
public:
    Material();
    Material(Shader *shader);
    Material(string vertexPath, string fragPath);

    void AddTexture(Texture *texture);
    void RemoveTexture(unsigned int textureId);
    ~Material();

private:
    Shader *shader = nullptr;
    vector<Texture *> textureList;
};
