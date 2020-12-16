#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

class Shader
{
public:
    GLuint Program;
    Shader(const GLchar *vertexPath, const GLchar *fragmentPath);
    Shader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *geometryPath);

    void Use();
    Shader *SetVec3(string target, glm::vec3 value);
    Shader *SetVec2(string target, glm::vec2 value);
    Shader *SetFloat(string target, float value);
    Shader *SetInt(string target, int value);
    Shader* SetMat4(string target, glm::mat4 value);

private:
    void CreateShader(const GLchar *path, GLuint &shader, GLenum shaderType);
    void CreateShaderProgram(GLuint shaders[], int shadersCount, GLuint &program);
    void CheckShaderProgram(GLuint shaderProgram);
};