#version 330 core

struct Material
{
	sampler2D ambientLightMap;
	sampler2D specularLightMap;
	float shininess;
};

struct Light
{
	vec3 lightColor;
	vec3 lightPosition;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 color;


void main()
{
	//ambientLight
	vec3 ambientLight=light.ambient*light.lightColor;

	//diffuseLight
	vec3 lightDir=normalize(light.lightPosition-FragPos);
	vec3 diffuseLight=max(dot(lightDir,Normal),0)*light.diffuse*light.lightColor;

	//specularLight
	vec3 viewDir=normalize(viewPos-FragPos);
	vec3 reflectDir=reflect(-lightDir,Normal);
	float specularLightStrength=pow(max(dot(viewDir,reflectDir),0),material.shininess);
	vec3 specularLight=specularLightStrength*light.specular*light.lightColor;

	vec3 materialDiffuseAmbient=vec3(texture(material.ambientLightMap,TexCoord));
	//vec3 resultColor=(ambientLight+diffuseLight)*materialDiffuseAmbient+specularLight*material.specular;
	vec3 resultColor=(ambientLight+diffuseLight)*materialDiffuseAmbient+specularLight*vec3(texture(material.specularLightMap,TexCoord));


	color=vec4(resultColor,1);
}