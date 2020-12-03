#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    // Normal:
    FragColor = texture(screenTexture, TexCoords);
}