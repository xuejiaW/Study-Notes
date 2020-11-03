
#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shiness;
};

uniform Material material;

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

uniform vec3 viewPos;

out vec4 color;
in vec3 fragPos;
in vec3 normal;

void main()
{
    vec3 ambientComponent = light.ambient * material.ambient;

    vec3 lightDir=normalize(light.position-fragPos);
    vec3 viewDir=normalize(viewPos-fragPos);
    vec3 reflectDir=reflect(-lightDir,normal);

    float diff=max(dot(normal,lightDir),0.0);
    vec3 diffuseComponent=diff*material.diffuse*light.diffuse;

    float spec=pow(max(dot(viewDir,reflectDir),0.0),material.shiness);
    vec3 specularComponent=spec*material.specular*light.specular;

    vec3 light=ambientComponent+diffuseComponent +specularComponent;
    color = vec4(light,1);
}
