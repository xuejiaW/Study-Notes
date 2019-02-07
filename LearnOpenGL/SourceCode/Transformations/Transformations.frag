#version 330 core

out vec4 color;

in vec2 TexCoord;

uniform sampler2D ourtexture1;
uniform sampler2D ourtexture2;

void main()
{
	//color=vec4(1.0f,0f,0f,1.0f);
	//color=texture(ourtexture2,TexCoord);
	color=mix(texture(ourtexture1,TexCoord),texture(ourtexture2,TexCoord),0.8f);
}