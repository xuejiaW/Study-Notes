#version 330 core

layout (location =1 ) in vec3 position;

void main()
{
	gl_Position=vec4(position*0.5,1.0f);
}