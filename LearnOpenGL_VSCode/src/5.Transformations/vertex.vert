#version 330 core

layout (location=0) in vec3 pos;
layout (location=1) in vec2 tex;

out vec2 texcoord;
uniform mat4 transform;

void main()
{
    gl_Position= transform*vec4(pos.xyz,1.0);
    texcoord=tex;
}