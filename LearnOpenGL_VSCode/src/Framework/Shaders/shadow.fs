#version 330 core

in VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
}
fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D depthMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 FragColor;

float ShaderCalculation(vec4 FragPosLightSpace, vec3 normal, vec3 lightDir)
{
    // perform projective divide, the result value range is [-1,1]
    vec3 projCoords = FragPosLightSpace.xyz / FragPosLightSpace.w;
    // The ProjectCoords is in NDC space which value range is [-1,1]
    // change the value range to [0,1] which is equal to the texture coordinate ranges
    projCoords = projCoords * 0.5 + 0.5;
    float closetDepth = texture(depthMap, projCoords.xy).r;

    // float bias = max(0.05 * (1 - dot(normal, lightDir)), 0.01);
    // float currentDepth = projCoords.z;
    // return currentDepth > closetDepth + bias ? 1.0 : 0.0;
    float currentDepth = projCoords.z;
    return currentDepth > closetDepth ? 1.0 : 0.0;
}

void main()
{
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);

    // ambient
    float ambient = 0.15;

    // diffuse
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diffuse = max(dot(lightDir, normal), 0.0);

    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 halfDir = normalize(lightDir + viewDir);
    float specular = pow(max(dot(normal, halfDir), 0.0), 64.0);

    float inShadow = ShaderCalculation(fs_in.FragPosLightSpace, normal, lightDir);
    vec3 lighting = (ambient + (1.0 - inShadow) * (diffuse + specular)) * color;
    FragColor = vec4(lighting, 1.0);
}