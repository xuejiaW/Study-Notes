#include <iostream>;
#define GLEW_STATIC
#include <GL/glew.h>;
#include <GLFW/glfw3.h>;
#include <SHADER.h>;

int main() 
{
	void Key_Callback(GLFWwindow *window, int key, int scan_code, int action, int mode);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, true);


	GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle_Pratice2", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		cout << "glew init fail";
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	GLfloat vertics1[] = 
	{
		-0.9f, -0.5f, 0.0f,  // Left 
		-0.0f, -0.5f, 0.0f,  // Right
		-0.45f, 0.5f, 0.0f,  // Top 
	};
	GLfloat vertics2[] = 
	{
		0.0f, -0.5f, 0.0f,  // Left
		0.9f, -0.5f, 0.0f,  // Right
		0.45f, 0.5f, 0.0f   // Top 
	};

	Shader shader("E:/Learn/LearnOpenGL/SourceCode/Triangle_Pratice2/Triangle_Pratice2.vert", "E:/Learn/LearnOpenGL/SourceCode/Triangle_Pratice2/Triangle_Pratice2.frag");

	GLuint VAO[2], VBO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertics1), vertics1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertics2), vertics2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glfwSetKeyCallback(window, Key_Callback);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.5f, 0.2, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glDeleteBuffers(2,VBO);
	glDeleteVertexArrays(2,VAO);
	glfwTerminate();
}

void Key_Callback(GLFWwindow *window,int key,int scan_code,int action,int mode)
{
	if (key==GLFW_KEY_ESCAPE && action ==GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}