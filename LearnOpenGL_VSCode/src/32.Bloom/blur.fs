#version 330 core
  
in vec2 TexCoords;

uniform sampler2D brightColor;

out vec4 FragColor;

uniform bool horizontal;
uniform float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void main()
{
    vec2 texelSize = 1.0 / textureSize(brightColor, 0); // gets size of single texel
     vec3 result = texture(brightColor, TexCoords).rgb * weight[0];
     if(horizontal)
     {
         for(int i = 1; i < 5; ++i)
         {
            result += texture(brightColor, TexCoords + vec2(texelSize.x * i, 0.0)).rgb * weight[i]; // Right part
            result += texture(brightColor, TexCoords - vec2(texelSize.x * i, 0.0)).rgb * weight[i]; // Left part
         }
     }
     else
     {
         for(int i = 1; i < 5; ++i)
         {
             result += texture(brightColor, TexCoords + vec2(0.0, texelSize.y * i)).rgb * weight[i]; // Up part
             result += texture(brightColor, TexCoords - vec2(0.0, texelSize.y * i)).rgb * weight[i]; // Down Part
         }
     }

     FragColor = vec4(result, 1.0);
}