#version 330 core

layout(location = 0) in vec3 Pos;
layout(location = 1) in vec2 TexCoords;
layout(location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out VS_OUT
{
    vec3 FragPos;
    vec2 TexCoords;
    mat3 TBN;

    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
}
vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix* aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N,T);

    mat3 TBN = mat3(T,B,N);
    mat3 inverseTBN = transpose(TBN);

    vs_out.FragPos = vec3(model * vec4(Pos, 1.0));
    vs_out.TexCoords = TexCoords;
    vs_out.TBN = TBN;
    vs_out.TangentLightPos = inverseTBN * lightPos;
    vs_out.TangentViewPos = inverseTBN * viewPos;
    vs_out.TangentFragPos = inverseTBN * vs_out.FragPos;

    gl_Position = projection * view * model * vec4(Pos, 1.0);
}