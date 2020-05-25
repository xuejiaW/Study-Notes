#include <iostream>;
#define GLEW_STATIC
#include <GL/glew.h>;
#include <GLFW/glfw3.h>;
#include <SOIL/SOIL.h>;
#include <glm/gtc/type_ptr.hpp>;
#include <glm/gtc/matrix_transform.hpp>;
#include <glm/glm.hpp>;
#include <SHADER.h>;

void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_Callback(GLFWwindow* window, double xpos, double ypos);
void scroll_Callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_Callback(GLFWwindow* window, int key, int action, int mode);


glm::vec3 cameraPos = glm::vec3(0, 0, 3);
glm::vec3 cameraFront = glm::vec3(0, 0, -1.0f);
glm::vec3 cameraUp = glm::vec3(0, 1, 0);

bool keys[1024];
void do_movement();
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
GLfloat lastX = 0, lastY = 0;
GLboolean firstMouse = true;

GLfloat fov = 45.0f;

//only when right button in mouse is clicking ,mouse move will work on
GLboolean ClickDown = false;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Camera_1", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		cout << "glew init fail" << endl;
		return -1;
	}

	GLint width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	GLfloat vertices[] = {
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

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Shader shader("../Camera_2/Camera_2.vert", "../Camera_2/Camera_2.frag");

	GLuint texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* image = SOIL_load_image("../container.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	image = SOIL_load_image("../Jiang.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glfwSetKeyCallback(window, key_Callback);
	glfwSetCursorPosCallback(window, mouse_Callback);
	glfwSetScrollCallback(window, scroll_Callback);
	glfwSetMouseButtonCallback(window, mouse_button_Callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	GLfloat radius = 10.0f;
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		do_movement();


		glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glUniform1i(glGetUniformLocation(shader.Program, "ourtexture1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glUniform1i(glGetUniformLocation(shader.Program, "ourtexture2"), 1);

		glm::mat4 view;
		view = glm::lookAt(cameraPos,cameraPos+cameraFront,cameraUp);
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 projection;
		glfwGetFramebufferSize(window, &width, &height);
		projection = glm::perspective(glm::radians(fov), (GLfloat)width / height, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		for (int i = 0; i < 10; ++i)
		{
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(20.0f)*i, glm::vec3(0, 1, 0));
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteTextures(1, &texture1);
	glDeleteTextures(1, &texture2);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
}
void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	////不应该在回调函数中进行移动控制，因为回调函数一次仅能对一个按键进行响应，如同时按下w和d，并不会斜对角移动

	//if (key==GLFW_KEY_W)
	//{
	//	cameraPos += cameraSpeed*cameraFront;
	//}
	//if (key==GLFW_KEY_S)
	//{
	//	cameraPos -= cameraSpeed*cameraFront;
	//}
	//if (key==GLFW_KEY_A)
	//{
	//	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp))*cameraSpeed;
	//	//这里需要对向量进行标准化（使向量的长度始终为1），保证速度大小不会因为方向而不同
	//}
	//if (key == GLFW_KEY_D)
	//{
	//	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp))*cameraSpeed;
	//}

	//用key激活，在其他函数中进行移动控制
	if (action == GLFW_PRESS)//press 控制按下的一瞬间状态
	{
		keys[key] = GL_TRUE;
	}
	else if (action==GLFW_RELEASE)
	{
		keys[key] = GL_FALSE;
	}
}

void do_movement() 
{
	GLfloat cameraSpeed = 5.0f*deltaTime;
	if (keys[GLFW_KEY_W])
	{
		cameraPos += cameraSpeed*cameraFront;
	}
	if (keys[GLFW_KEY_S])
	{
		cameraPos -= cameraSpeed*cameraFront;
	}
	if (keys[GLFW_KEY_A])
	{
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp))*cameraSpeed;
		//这里需要对向量进行标准化（使向量的长度始终为1），保证速度大小不会因为方向而不同
	}
	if (keys[GLFW_KEY_D] )
	{
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp))*cameraSpeed;
	}
}

void mouse_Callback(GLFWwindow* window,double xpos,double ypos) 
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
	}
	firstMouse = GL_FALSE;
	if (ClickDown)//
	{
		GLfloat xOffset = xpos - lastX;
		GLfloat yOffset = ypos - lastY;
		lastX = xpos;
		lastY = ypos;

		GLfloat sensitivity = 0.01f;
		xOffset *= sensitivity;
		yOffset *= -sensitivity;

		yaw += xOffset;
		pitch += yOffset;

		if (pitch>89.0f)
		{
			pitch = 89.0f;
		}
		if (pitch<-89.0f)
		{
			pitch = -89.0f;
		}

		glm::vec3 front;
		front.x = cos(glm::radians(yaw))*cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
	}	
}

void scroll_Callback(GLFWwindow* window,double xoffset,double yoffset) 
{
	if (fov>=1.0f && fov<=90.0f)
	{
		fov -= yoffset;
	}
	if (fov<=1.0f)
	{
		fov = 1.0f;
	}
	if (fov>=90.0f)
	{
		fov = 90.0f;
	}
}

void mouse_button_Callback(GLFWwindow* window,int key,int action,int mode) 
{
	if (key == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (action==GLFW_PRESS)
		{
			ClickDown = GL_TRUE;
		}
		else if (action==GLFW_RELEASE)
		{
			ClickDown = GL_FALSE;
		}
	}
}