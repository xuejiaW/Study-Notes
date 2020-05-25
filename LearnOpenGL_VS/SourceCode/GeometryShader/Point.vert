#version 330 core

layout(location = 0) in vec2 Pos;
layout(location =1) in vec3 Color;

out VS_OUT
{
	vec3 color;
}vs_out;

void main()
{
	gl_Position=vec4(Pos,0,1);
	vs_out.color=Color;
}