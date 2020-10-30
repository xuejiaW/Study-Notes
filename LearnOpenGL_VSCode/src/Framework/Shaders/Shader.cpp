#include "Shader.h"

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath, const GLchar *geometryPath)
{
    GLuint vertex, fragment, geometry;
    CreateShader(vertexPath, vertex, GL_VERTEX_SHADER);
    CreateShader(fragmentPath, fragment, GL_FRAGMENT_SHADER);
    CreateShader(geometryPath, geometry, GL_GEOMETRY_SHADER);
    CreateShaderProgram(new GLuint[3]{vertex, fragment, geometry}, 3, this->Program);
    CheckShaderProgram(this->Program);
}

Shader::Shader(const GLchar *vertexPath, const GLchar *fragmentPath)
{
    GLuint vertex, fragment;
    CreateShader(vertexPath, vertex, GL_VERTEX_SHADER);
    CreateShader(fragmentPath, fragment, GL_FRAGMENT_SHADER);
    CreateShaderProgram(new GLuint[2]{vertex, fragment}, 2, this->Program);
    CheckShaderProgram(this->Program);
}

void Shader::Use()
{
    glUseProgram(this->Program);
}

void Shader::CreateShaderProgram(GLuint shaders[], int shadersCount, GLuint &program)
{
    program = glCreateProgram();

    for (int i = 0; i < shadersCount; i++)
        glAttachShader(program, shaders[i]);

    glLinkProgram(program);
}

void Shader::CreateShader(const GLchar *path, GLuint &shader, GLenum shaderType)
{
    string Code;
    ifstream File;
    try
    {
        File.open(path);
        stringstream shaderStream;
        shaderStream << File.rdbuf();
        File.close();
        Code = shaderStream.str();
    }
    catch (const ifstream::failure &e) //TODO: warning
    {
        std::cout << "ERROR_SHADER_NOT_SUCCESSFULLY_READ" << endl;
    }

    const GLchar *ShaderCode = Code.c_str();

    GLint success;
    GLchar infoLog[512];

    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &ShaderCode, nullptr);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        cout << "ERROE_VERTEX_SHADER_COMPILE" << infoLog << endl;
    }
}

void Shader::CheckShaderProgram(GLuint shaderProgram)
{
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, 0, infoLog);
        cout << "ERROE_LINK_PROGRAM" << infoLog << endl;
    }
}

Shader *Shader::SetVec3(string target, glm::vec3 value)
{
    glUseProgram(this->Program);
    glUniform3fv(glGetUniformLocation(this->Program, target.c_str()), 1, value_ptr(value));
    return this;
}