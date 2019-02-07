#version 330 core

uniform vec3 lampColor;

out vec4 color;

void main()
{
	color=vec4(lampColor,1);
}