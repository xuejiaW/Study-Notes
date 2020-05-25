#include <iostream>;
#define GLEW_STATIC
#include <GL/glew.h>;
#include <GLFW/glfw3.h>;
#include <SHADER.h>;

int main() 
{
	void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle_Pratice3", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (glewInit()!=GLEW_OK)
	{
		cout << "glew init fail";
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	GLfloat vertics[] = 
	{
		-1,-0.5f,0,
		0,-0.5f,0,
		-0.5f,0.5f,0
	};

	GLfloat vertics2[] =
	{
		0,-0.5f,0,
		1,-0.5f,0,
		0.5f,0.5f,0
	};

	GLuint VAO[2], VBO[2];
	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertics), vertics, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertics2), vertics2, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);


	Shader shader_1("../Triangle_Pratice3/Triangle_Pratice3.vert", "../Triangle_Pratice3/Triangle_Pratice3.frag");
	Shader shader_2("../Triangle_Pratice3/Triangle_Pratice3_2.vert", "../Triangle_Pratice3/Triangle_Pratice3_2.frag");
	//在while循环前，VAO与VBO其实并未传递给着色器，所以着色器写在VAO和VBO的设置前后并无关系

	glfwSetKeyCallback(window, Key_Callback);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//while循环中，VAO与VBO传递给着色器，所以在绑定VAO之前，必须先启用相应的着色器程序
		shader_1.Use();
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		//例如这里我们用了shader_2着色器，那么对VAO[1]中的所有定义都会传输给shader_2,如layout数据的传递等等
		shader_2.Use();
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(2, VAO);
	glDeleteBuffers(2, VBO);
	glfwTerminate();
}

void Key_Callback(GLFWwindow* window,int key,int scancode,int action,int mode)
{
	if (key==GLFW_KEY_ESCAPE&& action==GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}