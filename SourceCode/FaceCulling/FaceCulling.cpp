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
#include <WINDOW.h>
#include <Utils.h>

using namespace glm;

Window window = Window("FaceCulling", 800, 600);
GLuint CubeVBO, CubeVAO;
GLuint CubeTex;
Shader shader("E:/Learn/LearnOpenGL/SourceCode/FaceCulling/FaceCulling.vert",
	"E:/Learn/LearnOpenGL/SourceCode/FaceCulling/FaceCulling.frag");

void Render();

int main()
{
	UpdateVAOVBO_3Pos2Normal(CubeVAO, CubeVBO, cubeVertices, sizeof(cubeVertices));
	UpdateTexture(CubeTex, "E:/Learn/LearnOpenGL/SourceCode/container.jpg", GL_REPEAT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	window.SetRenderFunction(Render);
	window.MainLoop();
}

void Render()
{
	shader.Use();
	mat4 view = camera.GetViewMatrix();
	mat4 projection = perspective(camera.Zoom, (GLfloat)(window.windowWidth / window.windowHeight), 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, value_ptr(mat4()));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,CubeTex);
	glBindVertexArray(CubeVAO);
	glDrawArrays(GL_TRIANGLES,0, 36);
}