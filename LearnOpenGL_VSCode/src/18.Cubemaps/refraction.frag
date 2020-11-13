#version 330 core
out vec4 FragColor;

in vec3 normal;
in vec3 position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
    float ratio= 1.00 /1.52; // glass refraction
    vec3 viewDirection = normalize(position - cameraPos);
    vec3 refraction = refract(viewDirection, normalize(normal),ratio);
    FragColor = vec4(texture(skybox, refraction).rgb, 1.0);
}