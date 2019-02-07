#version 330 core

in vec2 Texcoord;
out vec4 resultColor;

uniform sampler2D cubeTex;

void main()
{
	resultColor=texture(cubeTex,Texcoord);
	//resultColor=vec4(1,0,0,1);
}