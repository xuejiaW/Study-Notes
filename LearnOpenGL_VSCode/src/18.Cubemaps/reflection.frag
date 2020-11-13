#version 330 core
out vec4 FragColor;

in vec3 normal;
in vec3 position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{             
    vec3 viewDirection = normalize(position - cameraPos);
    vec3 reflection = reflect(viewDirection, normalize(normal));
    FragColor = vec4(texture(skybox, reflection).rgb, 1.0);
}