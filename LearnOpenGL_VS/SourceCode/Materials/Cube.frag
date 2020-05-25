#version 330 core

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 lightColor;
	vec3 lightPos;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;
uniform float ambient;

uniform Material material;
uniform Light light;

out vec4 color;

void main()
{
	//ambient light
	vec3 ambientLight=light.ambient*light.lightColor;
	
	//diffuse light
	vec3 normal=normalize(Normal);
	vec3 lightDir=normalize(light.lightPos-FragPos);
	float diffStrength=max(dot(normal,lightDir),0);
	vec3 diffLight=diffStrength*light.diffuse*light.lightColor;

	//specular light
	vec3 viewDir=normalize(viewPos-FragPos);
	vec3 reflectDir=reflect(-lightDir,normal);
	float specularStrength=pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specularLight=specularStrength*light.specular*light.lightColor;

	vec3 resultColor=ambientLight*material.ambient+diffLight*material.diffuse+specularLight*material.specular;

	color=vec4(resultColor,1);
}