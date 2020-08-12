#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

static int windowWidth = 800;
static int windowHeight = 800;

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "LearnOpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.0f, 1.f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    return 0;
}