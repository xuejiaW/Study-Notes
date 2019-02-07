#version 330 core

out vec4 Color;

in VS_OUT
{
	vec2 texcoord;
	vec3 normal;
}fs_in;

uniform sampler2D texture_diffuse;

void main()
{
	//Color=vec4(1,0,0,1);
	Color=texture(texture_diffuse,fs_in.texcoord);
}