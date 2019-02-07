#version 330 core

in vec2 Texcoord;
out vec4 Result;
uniform sampler2D ourTexture1;

void main()
{
	vec4 Color=texture(ourTexture1,Texcoord);
	if(Color.a<0.1f)
		discard;
	Result=Color;
	//Color=vec4(Texcoord,0,1);
}