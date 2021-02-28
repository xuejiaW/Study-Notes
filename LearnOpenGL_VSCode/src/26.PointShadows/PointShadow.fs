
#version 330 core

in VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
}
fs_in;

uniform sampler2D diffuseTexture;
uniform samplerCube depthMap;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float far_plane;

out vec4 FragColor;

float ShaderCalculation(vec3 fragPos, vec3 normal, vec3 lightDir)
{
    vec3 fragToLight = fragPos - lightPos;
    float currentDepth = length(fragToLight);

    // Without PCF
    // float closestDepth = texture(depthMap,fragToLight).r;
    // closestDepth *= far_plane;

    // float shadow =(currentDepth>closestDepth + bias ? 1.0 : 0.0);
    // return shadow;

    // Complete PCF
    // float bias = max(0.05 * (1 - dot(normal, lightDir)), 0.01);
    // float shadow = 0.0;
    // float offset = 0.1;
    // float samples = 4.0;

    // for(float x = -offset; x < offset; x += (offset*2)/samples )
    // {
    //         for(float y = -offset; y < offset; y += (offset*2)/samples )
    //         {
    //             for(float z = -offset; z < offset; z += (offset*2)/samples )
    //             {
    //                 float closestDepth = texture(depthMap,fragToLight + vec3(x, y, z)).r;
    //                 closestDepth *= far_plane;
    //                 shadow += (currentDepth>closestDepth + bias ? 1.0 : 0.0);
    //             }
    //         }
    // }
    // shadow /= (samples * samples *samples);

    // Simplified PCF
    float bias = max(0.1 * (1 - dot(normal, lightDir)), 0.1);
    float shadow = 0.0;
    float diskRadius = 0.05;
    vec3 sampleOffsetDirections[20] = vec3[]
    (
       vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
       vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
       vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
       vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
       vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
    );

    for(int i = 0; i != 20; ++i)
    {
        float closestDepth = texture(depthMap,fragToLight + sampleOffsetDirections[i] * diskRadius  ).r;
        closestDepth *= far_plane;
        shadow += (currentDepth>closestDepth + bias ? 1.0 : 0.0);
    }

    shadow /= 20;

    return shadow;
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

    float inShadow = ShaderCalculation(fs_in.FragPos, normal, lightDir);

    vec3 lighting = (ambient + (1.0 - inShadow) * (diffuse + specular)) * color;

    FragColor = vec4(lighting, 1.0);
}