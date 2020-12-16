#version 330 core

in vec2 texcoord;
in vec3 normal;

uniform vec3 baseColor = vec3(1, 0, 0);
out vec4 FragColor;

void main()
{
    FragColor = vec4(baseColor, 1);
}