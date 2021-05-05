#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    const float gamma = 2.2;
    const float exposure = 5.0;

    vec3 hdrColor = texture(screenTexture, TexCoords).rgb;

    // // None Tone Mapping
    // vec3 mapped = hdrColor;
  
    // // Reinhard Tone Mapping
    // vec3 mapped = hdrColor / (hdrColor + vec3(1.0));

    // Exposure Tone Mapping
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);

    // Gamma Correction 
    mapped = pow(mapped, vec3(1.0 / gamma));
  
    FragColor = vec4(mapped, 1.0);
}