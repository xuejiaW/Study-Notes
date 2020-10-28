#pragma once

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using glm::mat4;
using glm::vec3;
using glm::vec4;
using std::cout;
using std::endl;
using std::string;

class Debug
{
private:
    Debug();
    ~Debug();

public:
    static void Log(string, int);
    static void Log(string, float);
    static void Log(string, vec3);
};
