#version 330 core

layout (location =0 ) in vec2 pos;
layout (location =1 ) in vec3 color;
layout (location =2 ) in vec2 offset;

out vec3 Color;

void main()
{
	vec2 aPos = pos * (gl_InstanceID / 100.0);
	gl_Position=vec4(aPos+offset,0,1);
	Color=color;
}