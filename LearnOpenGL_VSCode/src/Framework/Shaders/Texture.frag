#version 330 core

in vec2 texcoord;
in vec3 normal;

uniform vec4 baseColor = vec4(1, 1, 1, 1);
uniform sampler2D ourTexture;
out vec4 FragColor;

void main()
{
    FragColor = texture(ourTexture, texcoord);
}