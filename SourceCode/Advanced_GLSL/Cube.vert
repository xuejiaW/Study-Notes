#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1 ) in vec2 texcoord;

uniform mat4 model;

layout(std140) uniform Matrices
{
	uniform mat4 projection;
	uniform mat4 view;
};


out vec2 Texcoord;

void main()
{
	gl_Position=projection*view*model*vec4(pos,1.0);
	Texcoord=texcoord;
}