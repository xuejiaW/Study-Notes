#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    // Normal:
    FragColor = texture(screenTexture, TexCoords);
    FragColor.rgb = pow(FragColor.rgb,vec3(1.0/2.2));
}