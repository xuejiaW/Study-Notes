#version 330 core

layout (location=0) in vec3 pos;
layout (location=1) in vec2 tex;
layout (location=2) in vec3 norm;

out vec2 texcoord;
out vec3 normal;

uniform mat4 model;

uniform vec2 offsets[100];

void main()
{
    vec2 offset=offsets[gl_InstanceID];
    gl_Position= model*vec4(pos.xyz,1.0)+vec4(offset,0,1);
    texcoord=tex;
    normal=normalize(mat3(transpose(inverse(model))) * norm);
}