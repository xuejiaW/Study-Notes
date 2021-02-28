#version 330 core

in vec4 FragPos;

uniform vec3 lightPos;
uniform float far_plane;

void main()
{
    float lightDistance = length(FragPos.xyz - lightPos);
    lightDistance = lightDistance / far_plane; // convert to [0,1]

    gl_FragDepth = lightDistance;
}
