#version 330 core

struct Material
{
	sampler2D ambientLightMap;
	sampler2D specularLightMap;
	float shininess;
};

struct DirLight
{
	vec3 lightDirection;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 lightPosition;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
	vec3 lightPosition;
	vec3 lightDirection;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
    float linear;
    float quadratic;

	float outCutOff;
	float inCutOff;
};

uniform Material material;
uniform vec3 viewPos;

uniform PointLight pointLight;
uniform DirLight dirLight;
uniform SpotLight spotLight;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 color;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir);
vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 fragPos,vec3 ViewDir);


void main()
{
	vec3 viewDir=normalize(viewPos-FragPos);
	vec3 resultColor=CalcDirLight(dirLight,Normal,viewDir)+
	CalcPointLight(pointLight,Normal,FragPos,viewDir)+
	CalcSpotLight(spotLight,Normal,FragPos,viewDir);
	color=vec4(resultColor,1);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 ambientLight=light.ambient;

	vec3 lightDir=normalize(-light.lightDirection);
	vec3 diffuseLight=max(dot(lightDir,normal),0)*light.diffuse;

	vec3 reflectLightDir=reflect(-lightDir,normal);
	vec3 specularLight=pow(max(dot(reflectLightDir,viewDir),0),material.shininess)*light.specular;

	vec3 DirLightColor=(ambientLight+diffuseLight)*vec3(texture(material.ambientLightMap,TexCoord))+
	specularLight*vec3(texture(material.specularLightMap,TexCoord));

	return DirLightColor;
}

vec3 CalcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir)
{
	float lightDist=length(light.lightPosition-fragPos);
	float attenuation=1/(light.constant+light.linear*lightDist+light.quadratic*(lightDist*lightDist));

	//vec3 ambientLight=light.ambient*attenuation;
	vec3 ambientLight=vec3(0,0,0);//Only Calucate one ambientLight


	vec3 lightDir=normalize(light.lightPosition-fragPos);
	vec3 diffuseLight=max(dot(lightDir,normal),0)*light.diffuse*attenuation;

	vec3 reflectLightDir=reflect(-lightDir,normal);
	vec3 specularLight=pow(max(dot(reflectLightDir,viewDir),0),material.shininess)*light.specular*attenuation;

	vec3 DirLightColor=(ambientLight+diffuseLight)*vec3(texture(material.ambientLightMap,TexCoord))+
	specularLight*vec3(texture(material.specularLightMap,TexCoord));

	return DirLightColor;
}


vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 fragPos,vec3 viewDir)
{
	float lightDist=length(light.lightPosition-fragPos);
	float attenuation=1/(light.constant+light.linear*lightDist+light.quadratic*(lightDist*lightDist));

	//vec3 ambientLight=light.ambient*attenuation;
	vec3 ambientLight=vec3(0,0,0);


	vec3 lightDir=normalize(light.lightPosition-fragPos);
	vec3 diffuseLight=max(dot(lightDir,normal),0)*light.diffuse*attenuation;

	vec3 reflectLightDir=reflect(-lightDir,normal);
	vec3 specularLight=pow(max(dot(reflectLightDir,viewDir),0),material.shininess)*light.specular*attenuation;

	float theta=dot(lightDir,normalize(-light.lightDirection));
	float epsilon=light.inCutOff-light.outCutOff;
	float intensity=clamp((theta-light.outCutOff)/epsilon,0.0,1.0);

	vec3 materialDiffuseColor=vec3(texture(material.ambientLightMap,TexCoord));
	vec3 SpotLightColor=ambientLight*materialDiffuseColor+
	diffuseLight*materialDiffuseColor*intensity+
	specularLight*vec3(texture(material.specularLightMap,TexCoord))*intensity;

	return vec3(SpotLightColor);
}