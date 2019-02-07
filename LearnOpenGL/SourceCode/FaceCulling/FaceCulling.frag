#version 330 core

in vec2 Texcoord;

uniform sampler2D texture1;

out vec4 Color;

void main()
{
	Color=texture(texture1,Texcoord);
}