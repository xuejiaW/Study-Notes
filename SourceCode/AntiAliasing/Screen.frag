#version 330 core

in vec2 Texcoord;
out vec4 resultColor;

uniform sampler2D cubeTex;

void main()
{
	resultColor=texture(cubeTex,Texcoord);
}