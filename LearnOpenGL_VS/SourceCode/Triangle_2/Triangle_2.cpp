#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SHADER.h>

void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode);
int main() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle_2", nullptr, nullptr);
	glfwMakeContextCurrent(window);


	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout << "Glew Init Fail";
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window,&width, &height);
	glViewport(0, 0, width, height);

	glfwSetKeyCallback(window, Key_Callback);

	GLfloat vertexs[] = 
	{
		-0.5f,-0.5f,0,
		-0.5f,0.5f,0,
		0.5f,0.5f,0,
		0.5f,-0.5f,0
	};

	GLuint index[] = 
	{
		0,1,3,
		1,2,3
	};

	Shader shader("../Triangle_2/vertex.vert","../Triangle_2/fragment.frag");

	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window)) 
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1,&VAO);

	glfwTerminate();
	return 0;
}

void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key==GLFW_KEY_ESCAPE && action ==GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}