#pragma once;

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 Position;
    glm::vec2 TexCoord;
    glm::vec3 Normal;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;

    static const glm::vec3 one;
    static const glm::vec3 zero;

    Vertex();
    Vertex(glm::vec3 position = zero, glm::vec2 texCoord = zero, glm::vec3 normal = zero, glm::vec3 tangent = zero, glm::vec3 bitangent = zero);
};
