#include <iostream>;
#define GLEW_STATIC
#include <GL/glew.h>;
#include <GLFW/glfw3.h>;
#include <SOIL/SOIL.h>;
#include <glm/gtc/matrix_transform.hpp>;
#include <glm/glm.hpp>;
#include <glm/gtc/type_ptr.hpp>;
#include <map>;
#include <SHADER.h>;
#include <CAMERA.h>;
#include <drawingData.h>

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
void UpdateTexture(GLuint &tid, string TexPath, GLint clmapMethod);

int main()
{
	GLuint windowWidth = 800, windowHeight = 600;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Blending", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glewInit();
	glViewport(0, 0, 800, 600);

	vector<glm::vec3> vegetation;
	vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
	vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
	vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
	vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
	vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));


	vector<glm::vec3> windows
	{
		glm::vec3(-2.0f, 0.0f, -0.6f),
		glm::vec3(2.0f, 0.0f, 0.4f),
		glm::vec3(1.3f, 0.0f, 0.8f),
		glm::vec3(-0.7f, 0.0f, -2.7f),
		glm::vec3(-0.1f, 0.0f, -0.5f)
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

	GLuint PlaneVBO, PlaneVAO;
	glGenVertexArrays(1, &PlaneVAO);
	glGenBuffers(1, &PlaneVBO);
	glBindVertexArray(PlaneVAO);
	glBindBuffer(GL_ARRAY_BUFFER, PlaneVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(planeVertices),planeVertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint TransparentVBO, TransparentVAO;
	glGenVertexArrays(1, &TransparentVAO);
	glGenBuffers(1, &TransparentVBO);
	glBindVertexArray(TransparentVAO);
	glBindBuffer(GL_ARRAY_BUFFER, TransparentVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	GLuint floorTex, cubeTex,grassTex,windowTex;
	UpdateTexture(floorTex, "E:/Learn/LearnOpenGL/SourceCode/Jiang.png",GL_REPEAT);
	UpdateTexture(cubeTex, "E:/Learn/LearnOpenGL/SourceCode/container.jpg",GL_REPEAT);
	UpdateTexture(grassTex, "E:/Learn/LearnOpenGL/SourceCode/Grass.png",GL_CLAMP_TO_EDGE);
	UpdateTexture(windowTex, "E:/Learn/LearnOpenGL/SourceCode/Window.png", GL_CLAMP_TO_EDGE);

	Shader shader("E:/Learn/LearnOpenGL/SourceCode/Blending/blending.vert",
		"E:/Learn/LearnOpenGL/SourceCode/Blending/blending.frag");

	Shader shader_discard("E:/Learn/LearnOpenGL/SourceCode/Blending/blending.vert",
		"E:/Learn/LearnOpenGL/SourceCode/Blending/blending_Discard.frag");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		CalculateDeletaTime();
		ProcessKeyInput(window);

		glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::map<float, glm::vec3> sorted;
		for (unsigned int i = 0; i < windows.size(); i++)
		{
			float distance = glm::length(camera.Position - windows[i]);
			sorted[distance] = windows[i];
		}

		mat4 view = camera.GetViewMatrix();
		mat4 projection = perspective(camera.Zoom,(GLfloat)(windowWidth/windowHeight),0.1f, 100.0f);

		shader.Use();
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE,value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, value_ptr(projection));
		
		glBindVertexArray(PlaneVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, floorTex);
		glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 0);
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"),1, GL_FALSE, value_ptr(mat4()));
		glDrawArrays(GL_TRIANGLES, 0, 6);


		glBindVertexArray(CubeVAO);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, cubeTex);
		glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 1);
		mat4 model = translate(mat4(), glm::vec3(-1.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::translate(mat4(), glm::vec3(2.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glBindVertexArray(TransparentVAO);//Draw the grass first
		shader_discard.Use();
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, value_ptr(projection));
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, grassTex);
		glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 3);
		for (int i = 0; i < vegetation.size(); i++)
		{
			glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, value_ptr(translate(mat4(), vegetation[i])));
			glDrawArrays(GL_TRIANGLES, 0,6);
		}

		glActiveTexture(GL_TEXTURE2);
		shader.Use();
		glBindTexture(GL_TEXTURE_2D, windowTex);
		glUniform1i(glGetUniformLocation(shader.Program, "ourTexture1"), 2);
		for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
		{
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, value_ptr(translate(mat4(), it->second)));
		glDrawArrays(GL_TRIANGLES, 0, 6);
		}


		glBindVertexArray(0);


		glfwSwapBuffers(window);

	}
}

void UpdateTexture(GLuint &tid, string TexPath,GLint clmapMethod)
{
	int width, height;
	glGenTextures(1, &tid);
	glBindTexture(GL_TEXTURE_2D, tid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clmapMethod);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clmapMethod);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	unsigned char* image = SOIL_load_image(TexPath.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
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

