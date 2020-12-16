#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 norm;

layout(std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;

out vec2 texcoord;
out vec3 normal;

void main()
{
    gl_Position = projection * view * model * vec4(aPos.xyz, 1.0);

    texcoord = tex;
    normal = normalize(mat3(transpose(inverse(model))) * norm);
}