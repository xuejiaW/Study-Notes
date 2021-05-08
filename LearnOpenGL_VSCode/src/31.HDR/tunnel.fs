#version 330 core

in VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

struct Light
{
    vec3 Position;
    vec3 Color;
};

uniform sampler2D diffuseTexture;
uniform Light lights[16];

out vec4 FragColor;


void main()
{
    vec3 color = texture(diffuseTexture,fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);

    vec3 ambient = vec3(0.0); // Do not consider ambient
    vec3 lighting = vec3(0.0);

    for(int i= 0 ;i != 16;++i)
    {
        vec3 lightDir = normalize(lights[i].Position - fs_in.FragPos);
        float diff = max(dot(lightDir , normal),0.0);
        vec3 diffuse = lights[i].Color * diff * color;
        vec3 result = diffuse;

        float distance = length(fs_in.FragPos - lights[i].Position);
        result *= 1/(distance * distance); // With Gamma correction

        lighting += result;
    }

    // FragColor = texture(diffuseTexture,fs_in.TexCoords);
    FragColor = vec4(lighting, 1.0);
}