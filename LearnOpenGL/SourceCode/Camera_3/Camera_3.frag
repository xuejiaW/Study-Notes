#version 330 core

in vec2 TexCoord;
out vec4 color;

uniform sampler2D ourtexture1;
uniform sampler2D ourtexture2;

void main()
{
	color=mix(texture(ourtexture1,TexCoord),texture(ourtexture2,TexCoord),0.2f);
}