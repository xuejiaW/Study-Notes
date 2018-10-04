#version 330 core

layout(location=0) in vec3 Pos;
layout(location=1) in vec3 Normal;
layout(location=2) in vec2 Texcoord;

out VS_OUT
{
	vec2 texcoord;
}vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vs_out.texcoord=Texcoord;
	gl_Position=projection * view * model * vec4(Pos,1.0);
}