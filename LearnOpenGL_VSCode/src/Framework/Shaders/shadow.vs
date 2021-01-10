#version 330 core

layout(location = 0) in vec3 Pos;
layout(location = 1) in vec2 TexCoords;
layout(location = 2) in vec3 Normal;

out VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
}
vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

void main()
{
    vs_out.FragPos = vec3(model * vec4(Pos, 1.0));
    vs_out.Normal = transpose(inverse(mat3(model))) * Normal;
    vs_out.TexCoords = TexCoords;
    vs_out.FragPosLightSpace = lightSpaceMatrix * model * vec4(Pos, 1.0);
    gl_Position = projection * view * model * vec4(Pos, 1.0);
}