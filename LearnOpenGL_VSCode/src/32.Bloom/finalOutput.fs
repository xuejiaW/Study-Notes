#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D blurredBrightColor;
uniform bool usingBloom;

void main()
{
    const float gamma = 2.2;
    const float exposure = 1.0;

    vec3 hdrColor = texture(screenTexture, TexCoords).rgb;

    if(usingBloom)
    {
       vec3 bloomColor = texture(blurredBrightColor,TexCoords).rgb;
       hdrColor += bloomColor;
    }

    // Exposure Tone Mapping
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);

    // Gamma Correction 
    mapped = pow(mapped, vec3(1.0 / gamma));
  
    FragColor = vec4(mapped, 1.0);
}
