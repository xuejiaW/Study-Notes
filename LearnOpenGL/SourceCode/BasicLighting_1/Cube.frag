#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 Color;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float ambientStrength;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	//ambient Light
	vec3 ambientLight=ambientStrength*lightColor;

	//Diffuse Light
	vec3 norm=normalize(Normal);
	vec3 lightDir=normalize(lightPos-FragPos);
	vec3 diffLight=max(dot(norm,lightDir),0.0)*lightColor;

	//Specular Light
	vec3 viewDir=normalize(viewPos-FragPos);
	vec3 reflectDir=reflect(-lightDir,norm);
	float spec=pow(max(dot(viewDir,reflectDir),0.0),32);
	vec3 specularLight=spec*lightColor;

	vec3 result=(ambientLight+diffLight+specularLight)*objectColor;

	Color=vec4(result,1.0);
}