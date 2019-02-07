#version 330 core

in vec2 texcoord;

out vec4 Color;
uniform sampler2D texture_diffuse;

void main()
{
	//Color=vec4(1,0,0,1);
	Color=texture(texture_diffuse,texcoord);
}