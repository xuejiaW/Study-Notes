#version 330 core

layout (location=0) in vec3 pos;
layout (location=1) in vec2 tex;
layout (location=2) in vec3 norm;

out VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_out;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vs_out.FragPos =  vec3(model*vec4(pos,1.0));
    vs_out.Normal=normalize(mat3(transpose(inverse(model)))* norm);
    vs_out.TexCoords=tex;

    // gl_Position = projection * view * model *vec4(pos,1.0);
    gl_Position = projection*view*model*vec4(pos.xyz,1.0);
}