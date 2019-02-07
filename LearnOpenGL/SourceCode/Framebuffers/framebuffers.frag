#version 330 core

in vec2 Texcoord;
out vec4 Color;

uniform sampler2D ourTexture;

void main()
{
	Color=texture(ourTexture,Texcoord);
}
