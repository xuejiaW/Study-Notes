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

Window window=Window("Blending", 800, 600);
vector<glm::vec3> vegetation;
GLuint CubeVBO, CubeVAO;
GLuint PlaneVBO, PlaneVAO;
GLuint TransparentVBO, TransparentVAO;
GLuint floorTex, cubeTex, grassTex, windowTex;
Shader shader("../Blending/blending.vert",
	"../Blending/blending.frag");
Shader shader_discard("../Blending/blending.vert",
	"../Blending/blending_Discard.frag");


vector<glm::vec3> windows
{
	glm::vec3(-2.0f, 0.0f, -0.6f),
	glm::vec3(2.0f, 0.0f, 0.4f),
	glm::vec3(1.3f, 0.0f, 0.8f),
	glm::vec3(-0.7f, 0.0f, -2.7f),
	glm::vec3(-0.1f, 0.0f, -0.5f)
};

void renderFunction();

int main()
{

	vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
	vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
	vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
	vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
	vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));

	UpdateVAOVBO_3Pos_2Texcoord(CubeVAO, CubeVBO, cubeVertices_3Pos_2Texcoord,sizeof(cubeVertices_3Pos_2Texcoord));
	UpdateVAOVBO_3Pos_2Texcoord(PlaneVAO, PlaneVBO, planeVertices_3Pos_2Texcoord,sizeof(planeVertices_3Pos_2Texcoord));
	UpdateVAOVBO_3Pos_2Texcoord(TransparentVAO, TransparentVBO, transparentVertices_3Pos_2Texcoord,sizeof(transparentVertices_3Pos_2Texcoord));

	UpdateTexture(floorTex, "../Jiang.png",GL_REPEAT);
	UpdateTexture(cubeTex, "../container.jpg",GL_REPEAT);
	UpdateTexture(grassTex, "../Grass.png",GL_CLAMP_TO_EDGE);
	UpdateTexture(windowTex, "../Window.png", GL_CLAMP_TO_EDGE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);

	window.SetRenderFunction(renderFunction);
	window.MainLoop();
	
}


void renderFunction()
{
	std::map<float, glm::vec3> sorted;
	for (unsigned int i = 0; i < windows.size(); i++)
	{
		float distance = glm::length(camera.Position - windows[i]);
		sorted[distance] = windows[i];
	}

	mat4 view = camera.GetViewMatrix();
	mat4 projection = perspective(camera.Zoom,(GLfloat)(window.windowWidth/window.windowHeight),0.1f, 100.0f);

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
}


