#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SHADER.h>

void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode);
int main() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle_pratice1", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (glewInit()!=GLEW_OK)
	{
		cout << "GlewInit fail";
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glfwSetKeyCallback(window,key_Callback);

	GLfloat vertics[] =
	{
		-0.5f,0.5f,0,
		-0.5f,-0.5f,0,
		0.5f,0.5f,0,
		0.6f,0.5f,0,
		0.6f,-0.5f,0,
		-0.4f,-0.5f,0
	};

	GLuint VAO,VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertics), vertics, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);


	Shader shader("../Triangle_Pratice1/Triangle_Pratice1.vert", "../Triangle_Pratice1/Triangle_Pratice1.frag");

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	glDeleteVertexArrays(1,&VAO);
	glDeleteBuffers(1,&VBO);
}
void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key==GLFW_KEY_ESCAPE && action ==GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
