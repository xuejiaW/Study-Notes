#version 330 core
layout (location = 0 )in vec3 position;
layout (location = 1 )in vec2 texCoord1;
layout (location = 2 )in vec2 texCoord2;

out vec2 TexCoord1;
out vec2 TexCoord2;

void main()
{
	gl_Position=vec4(position,1.0f);
	TexCoord1=texCoord1;
	TexCoord2=texCoord2;
}