#version 330 core

in vec3 Color;

out vec4 resultColor;

void main()
{
	resultColor=vec4(Color,1);
}