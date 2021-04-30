#pragma once

#include "../GameObjects/GameObject.h"
#include "../Mesh/Mesh.h"
#include "../Shaders/Shader.h"
#include "../Components/MeshRender.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>
#include <map>

class Model : public GameObject
{
public:
    Model(std::string path, Shader *shader);
    ~Model();

private:
    std::string modelPath;
    std::string modelPathDirectory;
    std::map<string, Texture *> str2TextureMap;
    std::vector<MeshRender *> meshRenderLists;

    Shader *usingShader;
    void ProcessModelNode(aiNode *node, const aiScene *scene);
    void ProcessModelMesh(MeshRender *meshRender, aiMesh *mesh, const aiScene *scene);
    void LoadVertexData(MeshRender *meshRender, aiMesh *mesh, const aiScene *scene);
    void LoadTexturesData(MeshRender *meshRender, aiMesh *mesh, const aiScene *scene);
    void LoadTexturesFromAIMaterial(aiMaterial *mat, Material *material, aiTextureType type, string typeName);

    Transform *transform;
};