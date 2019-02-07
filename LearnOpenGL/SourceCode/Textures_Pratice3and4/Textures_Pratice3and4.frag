#version 330 core

out vec4 color;
in	vec2 TexCoord;

uniform sampler2D ourtexture1;
uniform sampler2D ourtexture2;
uniform float mixlevel;

void main()
{
	//color=vec4(1.0f,0f,0f,1.0f);
	//color=texture(ourtexture2,TexCoord);
	color=mix(texture(ourtexture1,TexCoord),texture(ourtexture2,vec2(TexCoord.x,1-TexCoord.y)),mixlevel);
	//指第二个图片是80%
}