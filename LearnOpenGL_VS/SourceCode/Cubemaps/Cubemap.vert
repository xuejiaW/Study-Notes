#version 330 core

layout(location=0) in vec3 pos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	TexCoords=pos;
	vec4 pos=projection*view*vec4(pos,1);
	float w=pos.w;//if just make z==w it may cause z fighting
	gl_Position=vec4(pos.xy,w-0.01,w);
}