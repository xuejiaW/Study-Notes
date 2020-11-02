
#version 330 core

uniform float ambientStrength;
uniform float specularStrength;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 color;
in vec3 fragPos;
in vec3 normal;

void main()
{
    vec3 ambientComponent=ambientStrength*lightColor;

    vec3 lightDir=normalize(lightPos-fragPos);
    vec3 viewDir=normalize(viewPos-fragPos);
    vec3 reflectDir=reflect(-lightDir,normal);

    float diff=max(dot(normal,lightDir),0.0);
    float spec=pow(max(dot(viewDir,reflectDir),0.0),32);

    vec3 diffuseComponent=diff*lightColor;
    vec3 specularComponent=spec*lightColor*specularStrength;

    vec3 light=ambientComponent+diffuseComponent +specularComponent;
    color = vec4(light*objectColor,1);
}