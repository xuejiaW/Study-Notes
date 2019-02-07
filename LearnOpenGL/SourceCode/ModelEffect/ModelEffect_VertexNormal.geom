#version 330 core

layout(triangles) in;
layout(line_strip,max_vertices=6) out;

in VS_OUT
{
	vec2 texcoord;
	vec3 normal;
}gs_in[];


void GenereateLine(int index)
{
	gl_Position=gl_in[index].gl_Position;
	EmitVertex();
	gl_Position=gl_in[index].gl_Position+vec4(gs_in[index].normal,0.0)*0.05;
	EmitVertex();
	EndPrimitive();
}

void main()
{
	GenereateLine(0);
	GenereateLine(1);
	GenereateLine(2);
}