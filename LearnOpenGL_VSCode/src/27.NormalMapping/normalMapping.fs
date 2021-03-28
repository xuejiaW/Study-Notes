
#version 330 core

in VS_OUT
{
    vec3 FragPos;
    vec2 TexCoords;
    mat3 TBN;

    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
}
fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D normalMap;

uniform vec3 lightPos;
uniform vec3 viewPos;


out vec4 FragColor;

void main()
{
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;

    vec3 normal = texture(normalMap, fs_in.TexCoords).rgb;
    normal = normal * 2 - 1;

    // // Case 1 : Do not take TBN into account, will cause problem when surface rotate
    // normal = normalize(normal);  

    // // Case 2: transform normal to world space
    // normal = normalize(fs_in.TBN * normal); // Transform 
    // // ambient
    // float ambient = 0.15;
    // // diffuse
    // vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    // float diffuse = max(dot(lightDir, normal), 0.0);
    // // specular
    // vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    // vec3 halfDir = normalize(lightDir + viewDir);
    // float specular = pow(max(dot(normal, halfDir), 0.0), 64.0);

    // Case 3: transform others into tangent space
    normal = normalize(normal);
    // ambient
    float ambient = 0.15;
    // diffuse
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diffuse = max(dot(lightDir, normal), 0.0);
    // specular
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 halfDir = normalize(lightDir + viewDir);
    float specular = pow(max(dot(normal, halfDir), 0.0), 64.0);


    vec3 lighting = (ambient + (diffuse + specular)) * color;
    FragColor = vec4(lighting, 1.0);
}