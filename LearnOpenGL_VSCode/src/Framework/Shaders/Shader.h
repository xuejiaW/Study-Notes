#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <iostream>
using namespace std;

class Shader
{
public:
    GLuint Program;
    Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
    Shader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *geometryPath);

    void Use();

private:
    void CreateShader(const GLchar *path, GLuint &shader, GLenum shaderType);
    void CreateShaderProgram(GLuint shaders[], int shadersCount, GLuint &program);
    void CheckShaderProgram(GLuint shaderProgram);
};