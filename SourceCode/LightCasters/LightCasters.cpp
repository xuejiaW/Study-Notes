#include <iostream>
#define GLEW_STATIC
#include <Gl/glew.h>;
#include <GLFW/glfw3.h>;
#include <glm/glm.hpp>;
#include <glm/gtc/matrix_transform.hpp>;
#include <glm/gtc/type_ptr.hpp>;
#include <SOIl/SOIL.h>;
#include <SHADER.h>;
#include <CAMERA.h>;
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

	GLFWwindow *window = glfwCreateWindow(800, 600, "LightMap", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, Cursor_move_callback);
	glfwSetMouseButtonCallback(window, mouse_button_Callback);
	glfwSetScrollCallback(window, scroll_callback);

	glewInit();
	GLint width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	float vertices[] = {
		// positions // normals // texture coords
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	vec3 positions[] =
	{
		vec3(0,0,0),
		vec3(1, 0.5f, -2)
	};

	vec3 cubePositions[] = {
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

	GLuint VBO, CubeVAO, LampVAO;
	glGenVertexArrays(1, &CubeVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(CubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(GL_FLOAT)), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(GL_FLOAT)), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * (sizeof(GL_FLOAT)), (GLvoid*)(6 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &LampVAO);
	glBindVertexArray(LampVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(GL_FLOAT)), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint diffuseLightMap, specularLightMap;
	UpdateTexture(diffuseLightMap, "E:/Learn/LearnOpenGL/SourceCode/DiffuseLightingMap.png");
	UpdateTexture(specularLightMap, "E:/Learn/LearnOpenGL/SourceCode/SpecularLightingMap.png");

	Shader shader_Cube("E:/Learn/LearnOpenGL/SourceCode/LightCasters/Cube.vert",
		"E:/Learn/LearnOpenGL/SourceCode/LightCasters/Cube.frag");

	Shader shader_Lamp("E:/Learn/LearnOpenGL/SourceCode/LightCasters/Lamp.vert",
		"E:/Learn/LearnOpenGL/SourceCode/LightCasters/Lamp.frag");

	vec3 lightColor = vec3(1, 1, 1);
	shader_Lamp.Use();
	glUniform3fv(glGetUniformLocation(shader_Lamp.Program, "lampColor"), 1, value_ptr(lightColor));

	shader_Cube.Use();
	glUniform3fv(glGetUniformLocation(shader_Cube.Program, "material.ambient"), 1, value_ptr(vec3(0, 1, 1)));
	glUniform3fv(glGetUniformLocation(shader_Cube.Program, "material.diffuse"), 1, value_ptr(vec3(0, 1, 1)));
	glUniform3fv(glGetUniformLocation(shader_Cube.Program, "material.specular"), 1, value_ptr(vec3(0.5f, 0.5f, 0.5f)));
	glUniform1f(glGetUniformLocation(shader_Cube.Program, "material.shininess"), 32);

	glUniform3fv(glGetUniformLocation(shader_Cube.Program, "dirLight.lightDirection"), 1, value_ptr(vec3(-2.0f, -0.1f,0.0f)));
	glUniform3fv(glGetUniformLocation(shader_Cube.Program, "dirLight.ambient"), 1, value_ptr(vec3(0.1f, 0.1f, 0.1f)));
	glUniform3fv(glGetUniformLocation(shader_Cube.Program, "dirLight.diffuse"), 1, value_ptr(vec3(1.0f, 1.0f, 1.0f)));
	glUniform3fv(glGetUniformLocation(shader_Cube.Program, "dirLight.specular"), 1, value_ptr(vec3(1, 1, 1)));

	glUniform3fv(glGetUniformLocation(shader_Cube.Program, "pointLight.lightPosition"), 1, value_ptr(positions[1]));
	glUniform3fv(glGetUniformLocation(shader_Cube.Program, "pointLight.ambient"), 1, value_ptr(vec3(0.1f, 0.1f, 0.1f)));
	glUniform3fv(glGetUniformLocation(shader_Cube.Program, "pointLight.diffuse"), 1, value_ptr(vec3(0.5f, 0.5f, 0.5f)));
	glUniform3fv(glGetUniformLocation(shader_Cube.Program, "pointLight.specular"), 1, value_ptr(vec3(1, 1, 1)));
	glUniform1f(glGetUniformLocation(shader_Cube.Program, "pointLight.constant"),1.0f );
	glUniform1f(glGetUniformLocation(shader_Cube.Program, "pointLight.linear"),0.09f );
	glUniform1f(glGetUniformLocation(shader_Cube.Program, "pointLight.quadratic"),0.32f );

	glUniform3fv(glGetUniformLocation(shader_Cube.Program, "spotLight.ambient"), 1, value_ptr(vec3(0.1f, 0.1f, 0.1f)));
	glUniform3fv(glGetUniformLocation(shader_Cube.Program, "spotLight.diffuse"), 1, value_ptr(vec3(1.0f,1.0f, 1.0f)));
	glUniform3fv(glGetUniformLocation(shader_Cube.Program, "spotLight.specular"), 1, value_ptr(vec3(1, 1, 1)));
	glUniform1f(glGetUniformLocation(shader_Cube.Program, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(shader_Cube.Program, "spotLight.linear"), 0.09f);
	glUniform1f(glGetUniformLocation(shader_Cube.Program, "spotLight.quadratic"), 0.32f);
	glUniform1f(glGetUniformLocation(shader_Cube.Program, "spotLight.outCutOff"), cos(radians(12.5f)));
	glUniform1f(glGetUniformLocation(shader_Cube.Program, "spotLight.inCutOff"), cos(radians(8.0f)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseLightMap);
	glUniform1i(glGetUniformLocation(shader_Cube.Program, "material.ambientLightMap"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularLightMap);
	glUniform1i(glGetUniformLocation(shader_Cube.Program, "material.specularLightMap"), 1);

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		CalculateDeletaTime();
		ProcessKeyInput(window);

		glClearColor(0.2f, 0.2f, 0.2f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader_Cube.Use();

		mat4 view = camera.GetViewMatrix();
		mat4 projection = perspective(camera.Zoom, (GLfloat)width / height, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(shader_Cube.Program, "view"), 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader_Cube.Program, "projection"), 1, GL_FALSE, value_ptr(projection));
		glUniform3fv(glGetUniformLocation(shader_Cube.Program, "viewPos"), 1, value_ptr(camera.Position));
		glUniform3fv(glGetUniformLocation(shader_Cube.Program, "spotLight.lightPosition"), 1,value_ptr(camera.Position));
		glUniform3fv(glGetUniformLocation(shader_Cube.Program, "spotLight.lightDirection"), 1,value_ptr(camera.Front));


		glBindVertexArray(CubeVAO);
		mat4 model = mat4();
		for (GLuint index = 0; index < 10; index++)
		{
			model = translate(mat4(), cubePositions[index]);
			model = rotate(model,index*radians(20.0f),vec3(1, 0, 0));
			glUniformMatrix4fv(glGetUniformLocation(shader_Cube.Program, "model"), 1, GL_FALSE, value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);

		}
		glBindVertexArray(0);

		shader_Lamp.Use();
		model = translate(mat4(), positions[1]);
		model = scale(model, vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(glGetUniformLocation(shader_Lamp.Program, "view"), 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader_Lamp.Program, "model"), 1, GL_FALSE, value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader_Lamp.Program, "projection"), 1, GL_FALSE, value_ptr(projection));
		glBindVertexArray(LampVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	return -1;
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

void UpdateTexture(GLuint &targetTexture, string TexturePath)
{
	int width, height;
	glGenTextures(1, &targetTexture);
	glBindTexture(GL_TEXTURE_2D, targetTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* image = SOIL_load_image(TexturePath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
}
