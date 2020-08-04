#include "Engine.h"

Engine::Engine(int width, int height) : windowWidth(width), windowHeight(height)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(windowWidth, windowHeight, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void Engine::Run()
{
    if (initFunc)
        initFunc();
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 1.f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        if (mainLoop)
            mainLoop();
        glfwPollEvents();
    }
}

void Engine::SetMainLoop(void (*mainLoop)())
{
    this->mainLoop = mainLoop;
}

void Engine::SetInitFunc(void (*initFunc)())
{
    this->initFunc = initFunc;
}

Engine::~Engine()
{
    glfwTerminate();
}