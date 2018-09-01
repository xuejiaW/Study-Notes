#version 330 core

in vec2 Texcoord;
out vec4 Color;

uniform sampler2D outTexture;

void main()
{
	Color=texture(outTexture,Texcoord);
	//Color=vec4(Texcoord,0,1);
}