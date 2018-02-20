#version 330 core
out vec4 color;

in vec2 TexCoord1;
in vec2 TexCoord2;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
	//color=vec4(1.0f,0,0,1.0f);
	color=mix(texture(ourTexture1,TexCoord1),texture(ourTexture2,vec2(1-TexCoord2.x,1-TexCoord2.y)),0.5f);
	//要拿1减去数值，不然在gl_clamp_to_edge模式下会出现显示不完整
}