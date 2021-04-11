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
uniform sampler2D displacementMap;

uniform vec3 lightPos;
uniform vec3 viewPos;


out vec4 FragColor;

float depth_scale = 0.1;

// // Simple one
// vec2 ParallaxMapping(vec2 originTexCoords, vec3 viewDir)
// {
//     float depth = texture(displacementMap, originTexCoords).r;
//     vec2 p = (viewDir.xy / viewDir.z) * (depth * depth_scale);
//     return originTexCoords - p;
// }

// // Steep parallax Mapping
// vec2 ParallaxMapping(vec2 originTexCoords, vec3 viewDir)
// {
//     // // Hard Code layers count
//     // const float layersCount = 10;

//     // Adjust layers count according to the view direction
//     const float minLayersCount = 10.0;
//     const float maxLayersCount = 32.0;
//     float layersCount = mix(maxLayersCount, minLayersCount, max(dot(vec3(0,0,1),viewDir),0.0));

//     float layerDepthStep = 1.0 / layersCount;
//     float currentLayerDepth = 0.0;

//     vec2 P = viewDir.xy * depth_scale;
//     vec2 texCoordsBiasStep = P / layersCount;

//     vec2 currentTexCoords = originTexCoords;
//     float currentDisplaymentValue = texture(displacementMap,currentTexCoords).r;

//     while(currentLayerDepth < currentDisplaymentValue)
//     {
//         currentTexCoords -= texCoordsBiasStep;
//         currentDisplaymentValue = texture(displacementMap,currentTexCoords).r;
//         currentLayerDepth += layerDepthStep;
//     }

//     return currentTexCoords;
// }

// Parallax Occlusion Mapping
vec2 ParallaxMapping(vec2 originTexCoords, vec3 viewDir)
{
    const float minLayersCount = 10.0;
    const float maxLayersCount = 32.0;
    float layersCount = mix(maxLayersCount, minLayersCount, max(dot(vec3(0,0,1),viewDir),0.0));

    float layerDepthStep = 1.0 / layersCount;
    float currentLayerDepth = 0.0;

    vec2 P = viewDir.xy * depth_scale;
    vec2 texCoordsBiasStep = P / layersCount;

    vec2 currentTexCoords = originTexCoords;
    float currentDisplaymentValue = texture(displacementMap,currentTexCoords).r;

    while(currentLayerDepth < currentDisplaymentValue)
    {
        currentTexCoords -= texCoordsBiasStep;
        currentDisplaymentValue = texture(displacementMap,currentTexCoords).r;
        currentLayerDepth += layerDepthStep;
    }   
    // vec2 finalTexCoords = currentTexCoords;

    vec2 prevTexCoord = currentTexCoords + texCoordsBiasStep;
    float previousLayerDepth = currentLayerDepth - layerDepthStep;

    float belowSurfaceDepth = currentDisplaymentValue - currentLayerDepth; // Negative value
    float beyondSurfaceDepth = texture(displacementMap,prevTexCoord).r - previousLayerDepth;

    float weight = belowSurfaceDepth / (belowSurfaceDepth - beyondSurfaceDepth);

    vec2 finalTexCoords = prevTexCoord * weight + currentTexCoords*(1.0 - weight);

    return finalTexCoords;
}


void main()
{
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);

    // vec2 texCoords = fs_in.TexCoords;

    vec2 texCoords = ParallaxMapping(fs_in.TexCoords,viewDir);
    if(texCoords.x > 1.0 || texCoords.y > 1.0 || texCoords.x < 0.0 || texCoords.y < 0.0)
        discard;

    vec3 color = texture(diffuseTexture, texCoords).rgb;

    vec3 normal = texture(normalMap, texCoords).rgb;
    normal = normal * 2 - 1;

    normal = normalize(normal);
    // ambient
    float ambient = 0.15;
    // diffuse
    vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
    float diffuse = max(dot(lightDir, normal), 0.0);
    // specular
    vec3 halfDir = normalize(lightDir + viewDir);
    float specular = pow(max(dot(normal, halfDir), 0.0), 64.0);


    vec3 lighting = (ambient + (diffuse + specular)) * color;
    FragColor = vec4(lighting, 1.0);
}