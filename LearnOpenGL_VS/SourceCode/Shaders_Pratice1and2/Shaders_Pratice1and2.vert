#version 330 core
layout (location = 0) in vec3 position;
uniform float deviation;

void main()
{
	gl_Position=vec4(position.x+deviation,-position.y,position.z,1.0f);	//第一题只是在y变量前加负号即可
}
