
#version 330 core

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shiness;
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
    float spec=pow(max(dot(viewDir,reflectDir),0.0),material.shiness);
    vec3 specularComponent=spec*light.specular* vec3(texture(material.specular,texcoord));

    return ambientComponent + diffuseComponent + specularComponent;
}

void main()
{
    vec3 viewDir= normalize(viewPos-fragPos);
    vec3 reuslt=CalculateDirLight(dirLight,normal,viewDir);

    color = vec4(reuslt,1);
}
