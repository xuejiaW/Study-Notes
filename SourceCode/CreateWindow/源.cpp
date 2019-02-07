#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

const GLuint WIDTH = 800, HEIGHT = 600;

int main() 
{
	void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

	glfwInit();//Init GLFW

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//set OpenGL Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//set CoreProfile
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//Create Windows Object
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if ((window==nullptr))
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//make "window" be the current thread context

	//Initialize Glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) 
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	//Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	//glfwSetKeyCallback(window, key_callback);  
	glfwSetKeyCallback(window, key_callback);

	//Game loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glfwSwapBuffers(window);
	}

	//Terminate GLFW,clearing any resoureces allocated by GLFW
	glfwTerminate();
	return 0;

}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode) 
{
	if (key==GLFW_KEY_ESCAPE && action==GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}