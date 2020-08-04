#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>
using namespace std;

class Engine

{
public:
    int windowWidth;
    int windowHeight;
    void (*mainLoop)();
    void (*initFunc)();
    GLFWwindow *window;

    Engine(int width, int height);
    void SetMainLoop(void (*mainLoop)());
    void SetInitFunc(void (*initFunc)());
    void Run();

    virtual ~Engine();
};
