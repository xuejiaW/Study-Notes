#version 330 core

in vec2 texcoord;
in vec3 normal;

uniform vec4 baseColor=vec4(1,1,1,1);

out vec4 FragColor;

void main()
{
    if(gl_FragCoord.x <400)
        FragColor= vec4(1,0,0,1);
    else
        FragColor = vec4(0,1,0,1);
}