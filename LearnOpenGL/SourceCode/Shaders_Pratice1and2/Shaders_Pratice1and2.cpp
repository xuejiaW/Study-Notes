#include <iostream>;
#define GLEW_STATIC
#include <GL/glew.h>;
#include <GLFW/glfw3.h>;
#include <SHADER.h>;

int main() 
{
	void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode);


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Shaders_Pratice1and2", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (glewInit()!=GLEW_OK)
	{
		cout << "glew init fail";
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glfwSetKeyCallback(window, Key_Callback);

	GLfloat vertics[] = 
	{
		-0.5f,-0.5f,0,
		0.5f,-0.5f,0,
		0,0.5f,0
	};

	Shader shader("E:/Learn/LearnOpenGL/SourceCode/Shaders_Pratice1and2/Shaders_Pratice1and2.vert", "E:/Learn/LearnOpenGL/SourceCode/Shaders_Pratice1and2/Shaders_Pratice1and2.frag");

	GLuint VBO, VAO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertics), vertics, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	//glBindVertexArray(0);

	//第二题解答部分
	shader.Use();
	glUniform1f(glGetUniformLocation(shader.Program, "deviation"), 0.5f);
	//第二题解答部分

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.5f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
}
void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode) 
{
	if (key==GLFW_KEY_ESCAPE && action== GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}