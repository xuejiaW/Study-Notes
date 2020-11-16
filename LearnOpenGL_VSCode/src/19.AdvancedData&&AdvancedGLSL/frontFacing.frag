#version 330 core

in vec2 texcoord;
in vec3 normal;

uniform vec4 baseColor=vec4(1,1,1,1);

uniform sampler2D frontTexture;
uniform sampler2D backTexture;


out vec4 FragColor;

void main()
{
    if(gl_FrontFacing)
        FragColor = texture(frontTexture,texcoord);
    else
        FragColor = texture(backTexture,texcoord);
}