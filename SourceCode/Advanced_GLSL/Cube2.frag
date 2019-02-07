#version 330 core

in vec2 Texcoord;
out vec4 Color;

uniform sampler2D tex;

void main()
{
	Color=vec4(1,0,0,1);
}