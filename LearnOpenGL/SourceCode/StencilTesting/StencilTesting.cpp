#include <iostream>;
#define GLEW_STATIC
#include <GL/glew.h>;
#include <GLFW/glfw3.h>;
#include <SOIL/SOIL.h>;
#include <glm/gtc/matrix_transform.hpp>;
#include <glm/glm.hpp>;
#include <glm/gtc/type_ptr.hpp>;
#include <SHADER.h>;
#include <CAMERA.h>

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
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "StencilTesting", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, Cursor_move_callback);
	glfwSetMouseButtonCallback(window, mouse_button_Callback);
	glfwSetScrollCallback(window, scroll_callback);


	glewInit();

	GLint width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	float cubeVertices[] = {
		// positions          // texture Coords
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
	float planeVertices[] = {
		// positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	GLuint CubeVBO, CubeVAO;
	glGenVertexArrays(1, &CubeVAO);
	glGenBuffers(1, &CubeVBO);
	glBindVertexArray(CubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, CubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint floorTex, CubeTex;
	UpdateTexture(floorTex, "../Jiang.png");
	UpdateTexture(CubeTex, "../container.jpg");


	GLuint PlaneVBO, PlaneVAO;
	glGenVertexArrays(1, &PlaneVAO);
	glGenBuffers(1, &PlaneVBO);
	glBindVertexArray(PlaneVAO);
	glBindBuffer(GL_ARRAY_BUFFER, PlaneVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);



	Shader shader_Cube("../StencilTesting/stencil.vert",
		"../StencilTesting/stencil.frag");
	Shader shader_outline("../StencilTesting/stencil.vert",
		"../StencilTesting/outline.frag");
	//shader_Cube.Use();
	//shader_outline.Use();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glDepthFunc(GL_LESS);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		CalculateDeletaTime();
		ProcessKeyInput(window);

		glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
		mat4 view = camera.GetViewMatrix();
		mat4 projection = perspective(camera.Zoom, (GLfloat)width / height, 0.1f, 100.0f);
		shader_Cube.Use();
		glUniformMatrix4fv(glGetUniformLocation(shader_Cube.Program, "view"), 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader_Cube.Program, "projection"), 1, GL_FALSE, value_ptr(projection));
		shader_outline.Use();
		glUniformMatrix4fv(glGetUniformLocation(shader_outline.Program, "view"), 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader_outline.Program, "projection"), 1, GL_FALSE, value_ptr(projection));

		shader_Cube.Use();
		//draw the floor
		//glStencilFunc(GL_ALWAYS, 1, 0xff);
		glStencilMask(0x00);//Don't update stencil when drawing floor
		glBindVertexArray(PlaneVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, floorTex);
		glUniform1i(glGetUniformLocation(shader_Cube.Program, "ourTexture1"), 1);
		glUniformMatrix4fv(glGetUniformLocation(shader_Cube.Program, "model"), 1, GL_FALSE, value_ptr(mat4()));
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//draw cube
		glStencilMask(0xff);//Set stencil buffer to be 1 when drawing the cube
		glStencilFunc(GL_ALWAYS, 1, 0xff);
		glBindVertexArray(CubeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, CubeTex);
		glUniform1i(glGetUniformLocation(shader_Cube.Program, "ourTexture1"), 0);
		mat4 model = translate(mat4(), glm::vec3(-1.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader_Cube.Program, "model"), 1, GL_FALSE, value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::translate(mat4(), glm::vec3(2.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader_Cube.Program, "model"), 1, GL_FALSE, value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//draw outline
		glStencilFunc(GL_NOTEQUAL, 1, 0xff);
		glStencilMask(0x00);//the effect will still be corrent if we don't set 0x00,but it will increase wrilte operation
		glDisable(GL_DEPTH_TEST);//The outline should ignore the depth testing
		shader_outline.Use();
		glBindVertexArray(CubeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, CubeTex);
		glUniform1i(glGetUniformLocation(shader_outline.Program, "ourTexture1"), 0);
		model = translate(mat4(), glm::vec3(-1.0f, 0.0f, -1.0f));
		model = glm::scale(model, vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(glGetUniformLocation(shader_outline.Program, "model"), 1, GL_FALSE, value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::translate(mat4(), glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(glGetUniformLocation(shader_outline.Program, "model"), 1, GL_FALSE, value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glStencilMask(0xff);//Must set the 0xff or the next frame clear stencil buffer will failed


		glfwSwapBuffers(window);
	}
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
