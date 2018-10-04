#version 330 core

layout(location=0) in vec3 Pos;
layout(location=1) in vec3 Normal;
layout(location=2) in vec2 Texcoord;

out VS_OUT
{
	vec2 texcoord;
	vec3 normal;
}vs_out;

out vec2 texcoord;

layout(std140) uniform Matrices
{
	uniform mat4 view;
	uniform mat4 projection;
};

uniform mat4 model;

void main()
{
	vs_out.texcoord=Texcoord;
	mat3 normalMatrix = mat3(transpose(inverse(view * model)));
    vs_out.normal = normalize(vec3(projection * vec4(normalMatrix * Normal, 0.0)));
	gl_Position=projection * view * model * vec4(Pos,1.0);
}