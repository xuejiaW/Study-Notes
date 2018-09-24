#version 330 core

in vec3 Normal;
in vec2 Texcoord;
in vec3 Position;

out vec4 Color;

uniform vec3 camPos;
uniform sampler2D tex;
uniform samplerCube skybox;

void main()
{
	vec3 i=normalize(Position-camPos);

	//reflect
	vec3 r=reflect(i,normalize(Normal));

//	//refract
//	float ratio = 1.00 / 1.52;
//	vec3 r=refract(i, normalize(Normal), ratio);

	Color=vec4(texture(skybox,r).rgb,1.0);
}
