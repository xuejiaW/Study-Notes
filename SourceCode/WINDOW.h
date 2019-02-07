#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>;
#define GLEW_STATIC
#include <GL/glew.h>;
#include <GLFW/glfw3.h>;
#include <SOIL/SOIL.h>;
#include <glm/gtc/matrix_transform.hpp>;
#include <glm/glm.hpp>;
#include <glm/gtc/type_ptr.hpp>;
#include <map>;
#include <SHADER.h>;
#include <CAMERA.h>;
#include <drawingData.h>
#include <CAMERA.h>;
#include <Utils.h>

using namespace glm;
Camera camera;
void Cursor_move_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_Callback(GLFWwindow* window, int key, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void CalculateDeletaTime();
void ProcessKeyInput(GLFWwindow *window);

bool ClickDown;
bool firstFrame;
double lastMousePositionX;
double lastMousePositionY;
float deltaTime;
float lastFrameTime;

class  Window
{
public:
	GLFWwindow * window;
	GLuint windowWidth, windowHeight;

	Window();
	Window(std::string windowName,int width,int height);
	~ Window();

	void MainLoop();
	void SetRenderFunction(void(*renderFunction)());
private:
	void(*renderFunction)();
};

void Window::MainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		CalculateDeletaTime();
		ProcessKeyInput(window);

		if (renderFunction)
		{
			(*renderFunction)();
		}
		glfwSwapBuffers(window);
	}
}

void Window::SetRenderFunction(void(*renderFunction)())
{
	this->renderFunction = renderFunction;
}

Window::Window()
{
}

Window:: Window(std::string windowName, int width, int height)
{
	 this->windowWidth = width;
	 this->windowHeight = height;

	 glfwInit();
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	 glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	 glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	 window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	 glfwMakeContextCurrent(window);
	 glfwSetCursorPosCallback(window, Cursor_move_callback);
	 glfwSetMouseButtonCallback(window, mouse_button_Callback);
	 glfwSetScrollCallback(window, scroll_callback);
	 camera = Camera(vec3(0, 0, 3));
	 glewInit();
	 glViewport(0, 0, windowWidth, windowHeight);
}

 Window::~ Window()
{
}

 void Cursor_move_callback(GLFWwindow* window, double xpos, double ypos)
 {
	 if (!ClickDown)
	 {
		 firstFrame = true;
		 return;
	 }

	 if (firstFrame)
	 {
		 lastMousePositionX = xpos;
		 lastMousePositionY = ypos;
		 firstFrame = false;
	 }

	 float xOffset = xpos - lastMousePositionX;
	 float yOffset = ypos - lastMousePositionY;

	 lastMousePositionX = xpos;
	 lastMousePositionY = ypos;
	 camera.ProcessMouseMovement(xOffset, yOffset);

 }

 void mouse_button_Callback(GLFWwindow* window, int key, int action, int mode)
 {
	 if (key == GLFW_MOUSE_BUTTON_LEFT)
	 {
		 if (action == GLFW_PRESS)
		 {
			 ClickDown = GL_TRUE;
		 }
		 else if (action == GLFW_RELEASE)
		 {
			 ClickDown = GL_FALSE;
		 }
	 }
 }

 void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
 {
	 camera.ProcessMouseScroll(yoffset);
 }

 void ProcessKeyInput(GLFWwindow *window)
 {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 camera.ProcessKeyboard(FORWARD, deltaTime);
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 camera.ProcessKeyboard(BACKWARD, deltaTime);
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 camera.ProcessKeyboard(LEFT, deltaTime);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 camera.ProcessKeyboard(RIGHT, deltaTime);
	 if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		 camera.ProcessKeyboard(UP, deltaTime);
	 if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		 camera.ProcessKeyboard(DOWN, deltaTime);
 }

 void CalculateDeletaTime()
 {
	 float currentFrameTime = glfwGetTime();
	 deltaTime = currentFrameTime - lastFrameTime;
	 lastFrameTime = currentFrameTime;
 }

#endif // !WINDOW_H
