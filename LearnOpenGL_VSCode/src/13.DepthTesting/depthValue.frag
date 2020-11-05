
#version 330 core

in vec2 texcoord;
in vec3 normal;

out vec4 FragColor;

void main()
{    
    FragColor= vec4(vec3(gl_FragCoord.z),1);
}