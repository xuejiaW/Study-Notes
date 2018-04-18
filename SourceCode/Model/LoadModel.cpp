#include <iostream>
#define GLEW_STATIC
#include <Gl/glew.h>;
#include <GLFW/glfw3.h>;
#include <glm/glm.hpp>;
#include <glm/gtc/matrix_transform.hpp>;
#include <glm/gtc/type_ptr.hpp>;
#include "Model.h"
#include <Shader.h>
#include <Camera.h>

using namespace std;
using namespace glm;

Camera camera(vec3(0, 0, 3));
bool ClickDown;
bool firstFrame;
double lastMousePositionX;
double lastMousePositionY;
float deltaTime;
float lastFrameTime;

void ProcessKeyInput(GLFWwindow *window);
void CalculateDeletaTime();
void Cursor_move_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_Callback(GLFWwindow* window, int key, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void UpdateTexture(GLuint &targetTexture, string TexturePath);

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Model", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, Cursor_move_callback);
	glfwSetMouseButtonCallback(window, mouse_button_Callback);
	glfwSetScrollCallback(window, scroll_callback);

	glewInit();
	GLint width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	Shader shader("E:/Learn/LearnOpenGL/SourceCode/Model/model.vert",
		"E:/Learn/LearnOpenGL/SourceCode/Model/model.frag");

	Model ourModel("E:/Learn/LearnOpenGL/SourceCode/Model/nanoSuit/nanosuit.obj");

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		CalculateDeletaTime();
		ProcessKeyInput(window);

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();
		mat4 view = camera.GetViewMatrix();
		mat4 projection = perspective(camera.Zoom, (GLfloat)width / height, 0.1f, 100.0f);
		mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down

		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, value_ptr(projection));

		ourModel.Draw(shader);
		glfwSwapBuffers(window);
	}

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
