#version 330 core


in VS_OUT
{
    vec2 texcoord;
    vec3 normal;
}fs_in;


uniform vec4 baseColor=vec4(1,1,1,1);

uniform sampler2D frontTexture;
uniform sampler2D backTexture;


out vec4 FragColor;

void main()
{
    if(gl_FrontFacing)
        FragColor = texture(frontTexture,fs_in.texcoord);
    else
        FragColor = texture(backTexture,fs_in.texcoord);
}