#version 330 core

layout(location =0) in vec3 pos;
layout(location =1) in vec3 normal;
layout(location =2) in vec2 texcoord;;

out vec2 Texcoord;
out vec3 Position;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{

	Position=vec3(model*vec4(pos,1.0f));
	Texcoord=texcoord;
    Normal = mat3(transpose(inverse(model))) * normal;
	gl_Position=projection*view*model*vec4(pos,1.0f);

}