#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>;
#include <GLFW/glfw3.h>;
#include <glm/glm.hpp>;
#include <glm/gtc/matrix_transform.hpp>;
#include <glm/gtc/type_ptr.hpp>;
#include <SOIL/SOIL.h>
#include <SHADER.h>;
#include <CAMERA.h>
using namespace glm;

Camera camera(glm::vec3(0, 0, 3));

bool firstFrame = true;
bool ClickDown = false;

float deletaTime = 0.0f;
float lastFrameTime = 0.0f;

double lastMousePositionX = -1;
double lastMousePositionY = -1;

void ProcessKeyInput(GLFWwindow *window);
void CalculateDeletaTime();
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_Callback(GLFWwindow* window, int key, int action, int mode);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "Color_1", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_move_callback);
	glfwSetMouseButtonCallback(window, mouse_button_Callback);
	glfwSetScrollCallback(window, scroll_callback);

	if (glewInit()!=GLEW_OK)
	{
		cout << "glew Init fail";
		return -1;
	}

	GLint width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	GLfloat vertics[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	vec3 position[] =
	{
		vec3(0,0,0),
		vec3(1,1,0)
	};

	GLuint VBO,CubeVAO,LampVAO;
	glGenVertexArrays(1, &CubeVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(CubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertics), vertics, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * (sizeof(GL_FLOAT)), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &LampVAO);
	glBindVertexArray(LampVAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * (sizeof(GL_FLOAT)), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	Shader shader_Cube("E:/Learn/LearnOpenGL/SourceCode/Color_1/Cube.vert",
		"E:/Learn/LearnOpenGL/SourceCode/Color_1/Cube.frag");

	Shader shader_Lamp("E:/Learn/LearnOpenGL/SourceCode/Color_1/Lamp.vert",
		"E:/Learn/LearnOpenGL/SourceCode/Color_1/Lamp.frag");

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		CalculateDeletaTime();
		ProcessKeyInput(window);

		glClearColor(0.2f,0.2f,0.2f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		shader_Cube.Use();
		mat4 view = camera.GetViewMatrix();
		glUniformMatrix4fv(glGetUniformLocation(shader_Cube.Program, "view"), 1, GL_FALSE, value_ptr(view));
		mat4 projection=perspective(radians(camera.Zoom), (GLfloat)width / height, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader_Cube.Program, "projection"), 1, GL_FALSE, value_ptr(projection));
		mat4 model=mat4();
		model=translate(model,position[0]);
		glUniformMatrix4fv(glGetUniformLocation(shader_Cube.Program, "model"), 1, GL_FALSE, value_ptr(model));
		
		vec3 lightColor = vec3(1, 1, 1);
		glUniform3fv(glGetUniformLocation(shader_Cube.Program, "lightColor"), 1,value_ptr(lightColor));

		vec3 objectColor = vec3(1, 1, 0);
		glUniform3fv(glGetUniformLocation(shader_Cube.Program, "objectColor"), 1, value_ptr(objectColor));

		glBindVertexArray(CubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		shader_Lamp.Use();
		model = mat4();
		model = translate(model, position[1]);
		model = scale(model, vec3(0.2f));
		glUniformMatrix4fv(glGetUniformLocation(shader_Lamp.Program, "view"), 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader_Lamp.Program, "projection"), 1, GL_FALSE, value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(shader_Lamp.Program, "model"), 1, GL_FALSE, value_ptr(model));

		glUniform3fv(glGetUniformLocation(shader_Lamp.Program, "lightColor"), 1, value_ptr(lightColor));

		glBindVertexArray(LampVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &CubeVAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
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
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(FORWARD, deletaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(BACKWARD, deletaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(LEFT, deletaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(RIGHT, deletaTime);
	}
}

void CalculateDeletaTime()
{
	float currentFrameTime = glfwGetTime();
	deletaTime = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;
}