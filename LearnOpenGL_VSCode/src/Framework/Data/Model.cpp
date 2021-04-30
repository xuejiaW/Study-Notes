#include "../Debug.h"
#include "Model.h"
#include "Vertex.h"
#include "../Components/Texture.h"

Model::Model(std::string path, Shader *shader) : modelPath(path), usingShader(NULL), meshRenderLists(std::vector<MeshRender *>()),
                                                 str2TextureMap(), modelPathDirectory(""), GameObject(), transform(new Transform())
{
    if (shader->geometryPath != NULL && shader->geometryPath == "")
        usingShader = new Shader(shader->vertexPath, shader->fragmentPath, shader->geometryPath);
    else
        usingShader = new Shader(shader->vertexPath, shader->fragmentPath);

    modelPathDirectory = path.substr(0, path.find_last_of('/'));

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        Debug::Log(importer.GetErrorString());
        return;
    }

    ProcessModelNode(scene->mRootNode, scene);

    AddComponent(transform);
    for (int i = 0; i != meshRenderLists.size(); ++i)
    {
        AddComponent(meshRenderLists[i]);
    }
}

void Model::ProcessModelNode(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i != node->mNumMeshes; ++i)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; // Get actual mesh data from scene
        MeshRender *meshRender = new MeshRender(usingShader);
        ProcessModelMesh(meshRender, mesh, scene);
        meshRenderLists.push_back(meshRender);
    }

    // Recursively process children node
    for (unsigned int i = 0; i != node->mNumChildren; ++i)
    {
        ProcessModelNode(node->mChildren[i], scene);
    }
}

void Model::ProcessModelMesh(MeshRender *meshRender, aiMesh *aiMesh, const aiScene *scene)
{
    LoadVertexData(meshRender, aiMesh, scene);
    LoadTexturesData(meshRender, aiMesh, scene);
}

void Model::LoadVertexData(MeshRender *meshRender, aiMesh *aiMesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Load Vertex Data
    for (unsigned int i = 0; i != aiMesh->mNumVertices; ++i)
    {
        Vertex vertex;
        vertex.Position.x = aiMesh->mVertices[i].x;
        vertex.Position.y = aiMesh->mVertices[i].y;
        vertex.Position.z = aiMesh->mVertices[i].z;

        if (aiMesh->mTextureCoords[0])
        {
            // A Vertex may contain multiply texture coordinates, here we only use the first one
            vertex.TexCoord.x = aiMesh->mTextureCoords[0][i].x;
            vertex.TexCoord.y = aiMesh->mTextureCoords[0][i].y;

            vertex.Tangent.x = aiMesh->mTangents[i].x;
            vertex.Tangent.y = aiMesh->mTangents[i].y;
            vertex.Tangent.z = aiMesh->mTangents[i].z;

            vertex.Bitangent.x = aiMesh->mBitangents[i].x;
            vertex.Bitangent.y = aiMesh->mBitangents[i].y;
            vertex.Bitangent.z = aiMesh->mBitangents[i].z;
        }

        if (aiMesh->HasNormals())
        {
            vertex.Normal.x = aiMesh->mNormals[i].x;
            vertex.Normal.y = aiMesh->mNormals[i].y;
            vertex.Normal.z = aiMesh->mNormals[i].z;
        }

        vertices.push_back(vertex);
    }

    // Load indices
    for (unsigned int i = 0; i != aiMesh->mNumFaces; ++i)
    {
        aiFace face = aiMesh->mFaces[i];
        for (unsigned int j = 0; j != face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }

    Mesh *mesh = new Mesh(vertices, indices);
    meshRender->SetMesh(mesh);
}

void Model::LoadTexturesData(MeshRender *meshRender, aiMesh *aiMesh, const aiScene *scene)
{
    std::vector<Texture> textures;

    //Load Textures
    aiMaterial *aiMaterial = scene->mMaterials[aiMesh->mMaterialIndex];

    LoadTexturesFromAIMaterial(aiMaterial, meshRender->GetMaterial(), aiTextureType_DIFFUSE, "texture_diffuse");
    LoadTexturesFromAIMaterial(aiMaterial, meshRender->GetMaterial(), aiTextureType_SPECULAR, "texture_specular");
    LoadTexturesFromAIMaterial(aiMaterial, meshRender->GetMaterial(), aiTextureType_HEIGHT, "texture_normal");
    LoadTexturesFromAIMaterial(aiMaterial, meshRender->GetMaterial(), aiTextureType_AMBIENT, "texture_height");
}

void Model::LoadTexturesFromAIMaterial(aiMaterial *aMat, Material *material, aiTextureType type, string typeName)
{
    int textureCount = aMat->GetTextureCount(type);

    for (unsigned int i = 0; i != textureCount; ++i)
    {
        aiString textureStr;
        aMat->GetTexture(type, i, &textureStr);
        string texturePath = modelPathDirectory + "/" + string(textureStr.C_Str());

        Texture *texture = NULL;
        if (str2TextureMap.find(texturePath) != str2TextureMap.end())
        {
            texture = str2TextureMap[texturePath];
        }
        else
        {
            texture = new Texture(texturePath);
            str2TextureMap[texturePath] = texture;
        }

        material->AddTexture(typeName + to_string(i), texture);
    }
}