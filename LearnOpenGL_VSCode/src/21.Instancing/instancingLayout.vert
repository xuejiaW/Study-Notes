
#version 330 core

layout (location=0) in vec3 pos;
layout (location=1) in vec2 tex;
layout (location=2) in vec3 norm;
layout (location=3) in vec2 offset;

out vec2 texcoord;
out vec3 normal;

uniform mat4 model;

void main()
{
    vec3 aPos= pos*(gl_InstanceID)/100;
    gl_Position= model*vec4(aPos,1.0)+vec4(offset,0,1);
    texcoord=tex;
    normal=normalize(mat3(transpose(inverse(model))) * norm);
}