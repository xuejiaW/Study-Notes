
#version 330 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;
uniform vec3 ambient;

struct DirLight
{
    vec3 direction;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;

struct PointLight
{
    vec3 position;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform PointLight pointLights[2];

struct SpotLight
{
    vec3 position;
    vec3 direction;
    vec3 diffuse;
    vec3 specular;       

    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
};
uniform SpotLight spotLight;

uniform vec3 viewPos;

out vec4 color;
in vec2 texcoord;
in vec3 fragPos;
in vec3 normal;

vec3 GetDiffuseValue(vec3 normal,vec3 lightDir,vec3 lightDiffuse)
{
    return max(dot(normal, lightDir),0.0) * vec3(texture(material.diffuse,texcoord)) * lightDiffuse;
}

vec3 GetSpecularValue(vec3 normal,vec3 lightDir,vec3 viewDir, vec3 lightSpecular)
{
    vec3 reflectDir=reflect(-lightDir,normal);
    float spec=pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    vec3 specularComponent=spec*lightSpecular* vec3(texture(material.specular,texcoord));

    return specularComponent;
}

vec3 CalculateDirLight(DirLight light,vec3 normal,vec3 viewDir)
{
    vec3 lightDir=normalize(-light.direction);

    vec3 diffuseComponent= GetDiffuseValue(normal,lightDir,light.diffuse);
    vec3 specularComponent=GetSpecularValue(normal,lightDir,viewDir,light.specular);

    return diffuseComponent + specularComponent;
}

vec3 CalculatePointLight(PointLight light,vec3 normal, vec3 fragPos, vec3 viewDir)
{
    float lightDist = length(light.position - fragPos);
    float attenuation = 1 / (light.constant + light.linear*lightDist + light.quadratic*lightDist*lightDist);
    vec3 lightDir=normalize(light.position-fragPos);

    vec3 diffuseComponent=GetDiffuseValue(normal,lightDir,light.diffuse) * attenuation;
    vec3 specularComponent=GetSpecularValue(normal,lightDir,viewDir,light.specular) * attenuation;

    return diffuseComponent+specularComponent;
}

vec3 CalculateSpotLight(SpotLight light,vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float lightDist = length(light.position - fragPos);

     // attenuation
    float attenuation = 1.0 / (light.constant + light.linear * lightDist + light.quadratic * (lightDist * lightDist));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 diffuseComponent=GetDiffuseValue(normal,lightDir,light.diffuse)*attenuation*intensity;
    vec3 specularComponent=GetSpecularValue(normal,lightDir,viewDir,light.specular) * attenuation*intensity;

    return diffuseComponent+specularComponent;
}

void main()
{
    vec3 viewDir= normalize(viewPos-fragPos);

    vec3 ambientComponent = ambient * vec3(texture(material.diffuse,texcoord));

    vec3 result = ambientComponent;
    result += CalculateDirLight(dirLight,normal,viewDir);
    for(int i=0;i!=2;++i)
        result+=CalculatePointLight(pointLights[i],normal,fragPos,viewDir);
    result+=CalculateSpotLight(spotLight,normal,fragPos,viewDir);

    color = vec4(result,1);
}
