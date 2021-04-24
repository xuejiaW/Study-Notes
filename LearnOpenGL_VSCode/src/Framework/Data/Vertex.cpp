#include "Vertex.h"

const glm::vec3 Vertex::zero(0, 0, 0);
const glm::vec3 Vertex::one(1, 1, 1);

Vertex::Vertex() : Position(glm::vec3()), TexCoord(glm::vec2()), Normal(glm::vec3()), Tangent(glm::vec3()), Bitangent(glm::vec3())
{
}

Vertex::Vertex(glm::vec3 position, glm::vec2 texCoord, glm::vec3 normal, glm::vec3 tangent, glm::vec3 bitangent)
: Position(position), TexCoord(texCoord), Normal(normal), Tangent(tangent), Bitangent(bitangent)
{
}