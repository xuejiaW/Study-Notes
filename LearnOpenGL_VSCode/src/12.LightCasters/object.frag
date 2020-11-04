
#version 330 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;

struct DirLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirLight dirLight;

struct PointLight
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform PointLight pointLights[2];

uniform vec3 viewPos;

out vec4 color;
in vec2 texcoord;
in vec3 fragPos;
in vec3 normal;

vec3 CalculateDirLight(DirLight light,vec3 normal,vec3 viewDir)
{
    vec3 ambientComponent = light.ambient * vec3(texture(material.diffuse,texcoord));

    vec3 lightDir=normalize(-light.direction);
    float diff=max(dot(normal,lightDir),0.0);
    vec3 diffuseComponent=diff*light.diffuse*vec3(texture(material.diffuse,texcoord));

    vec3 reflectDir=reflect(-lightDir,normal);
    float spec=pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    vec3 specularComponent=spec*light.specular* vec3(texture(material.specular,texcoord));

    return ambientComponent + diffuseComponent + specularComponent;
}

vec3 CalculatePointLight(PointLight light,vec3 normal, vec3 fragPos, vec3 viewDir)
{
    float lightDist = length(light.position - fragPos);
    float attenuation = 1 / (light.constant + light.linear*lightDist + light.quadratic*lightDist*lightDist);

    vec3 lightDir=normalize(light.position-fragPos);
    float diff=max(dot(normal,lightDir),0.0) * attenuation;
    vec3 diffuseComponent=diff*light.diffuse*vec3(texture(material.diffuse,texcoord));

    vec3 reflectDir=reflect(-lightDir,normal);
    float spec=pow(max(dot(viewDir,reflectDir),0.0),material.shininess) * attenuation;
    vec3 specularComponent=spec*light.specular* vec3(texture(material.specular,texcoord));

    return diffuseComponent+specularComponent;
}

void main()
{
    vec3 viewDir= normalize(viewPos-fragPos);

    vec3 result= CalculateDirLight(dirLight,normal,viewDir);
    for(int i=0;i!=2;++i)
        result+=CalculatePointLight(pointLights[i],normal,fragPos,viewDir);

    color = vec4(result,1);
}
