#include "Mesh_Quad_TBN.h"
#include "../Debug.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Mesh_Quad_TBN::Mesh_Quad_TBN()
{
    // positions
    glm::vec3 pos0(-0.5f, -0.5f, 0.5f);
    glm::vec3 pos1(0.5f, -0.5f, 0.5f);
    glm::vec3 pos2(0.5f, 0.5f, 0.5f);
    glm::vec3 pos3(-0.5f, 0.5f, 0.5f);
    // texture coordinates
    glm::vec2 uv0(0.0f, 0.0f);
    glm::vec2 uv1(1.0f, 0.0f);
    glm::vec2 uv2(1.0f, 1.0f);
    glm::vec2 uv3(0.0f, 1.0f);
    // normal vector
    glm::vec3 nm(0.0f, 0.0f, 1.0f);

    // For the first triangle
    glm::vec3 edge1 = pos1 - pos0;
    glm::vec3 edge2 = pos2 - pos0;
    glm::vec2 edge1UV = uv1 - uv0;
    glm::vec2 edge2UV = uv2 - uv0;
    glm::vec3 tangent1, bitangent1;
    // DeletaU1 -> edge1UV.x
    // DeletaV1 -> edge1UV.y
    // DeletaU2 -> edge2UV.x
    // DeltaV2 -> edge2UV.y
    float determinant = 1.0f / (edge1UV.x * edge2UV.y - edge2UV.x * edge1UV.y);

    tangent1.x = (edge2UV.y * edge1.x - edge1UV.y * edge2.x) * determinant;
    tangent1.y = (edge2UV.y * edge1.y - edge1UV.y * edge2.y) * determinant;
    tangent1.z = (edge2UV.y * edge1.z - edge1UV.y * edge2.z) * determinant;
    bitangent1.x = (-edge2UV.x * edge1.x + edge1UV.x * edge2.x) * determinant;
    bitangent1.y = (-edge2UV.x * edge1.y + edge1UV.x * edge2.y) * determinant;
    bitangent1.z = (-edge2UV.x * edge1.z + edge1UV.x * edge2.z) * determinant;

    // For the second triangle
    edge1 = pos2 - pos0;
    edge2 = pos3 - pos0;
    edge1UV = uv2 - uv0;
    edge2UV = uv3 - uv0;
    glm::vec3 tangent2, bitangent2;
    // DeletaU1 -> edge1UV.x
    // DeletaV1 -> edge1UV.y
    // DeletaU2 -> edge2UV.x
    // DeltaV2 -> edge2UV.y
    determinant = 1.0f / (edge1UV.x * edge2UV.y - edge2UV.x * edge1UV.y);
    tangent2.x = (edge2UV.y * edge1.x - edge1UV.y * edge2.x) * determinant;
    tangent2.y = (edge2UV.y * edge1.y - edge1UV.y * edge2.y) * determinant;
    tangent2.z = (edge2UV.y * edge1.z - edge1UV.y * edge2.z) * determinant;
    bitangent2.x = (-edge2UV.x * edge1.x + edge1UV.x * edge2.x) * determinant;
    bitangent2.y = (-edge2UV.x * edge1.y + edge1UV.x * edge2.y) * determinant;
    bitangent2.z = (-edge2UV.x * edge1.z + edge1UV.x * edge2.z) * determinant;

    verticesList.push_back(Vertex(pos0, uv0, nm, tangent1, bitangent1));
    verticesList.push_back(Vertex(pos1, uv1, nm, tangent1, bitangent1));
    verticesList.push_back(Vertex(pos2, uv2, nm, tangent1, bitangent1));

    verticesList.push_back(Vertex(pos0, uv0, nm, tangent2, bitangent2));
    verticesList.push_back(Vertex(pos2, uv2, nm, tangent2, bitangent2));
    verticesList.push_back(Vertex(pos3, uv3, nm, tangent2, bitangent2));

    indicesList.insert(indicesList.end(), {0, 1, 2, 3, 4, 5});
}

Mesh_Quad_TBN::~Mesh_Quad_TBN() {}