#include <WINDOW.h>

Window window("Cubemap", 800, 600);

void Render();

GLuint cubemap,cubeTex;
GLuint skyboxVAO, skyboxVBO;
GLuint cubeVAO, cubeVBO;
vector<std::string> faces
{
	"E:/Learn/LearnOpenGL/SourceCode/skybox/right.jpg",
	"E:/Learn/LearnOpenGL/SourceCode/skybox/left.jpg",
	"E:/Learn/LearnOpenGL/SourceCode/skybox/top.jpg",
	"E:/Learn/LearnOpenGL/SourceCode/skybox/bottom.jpg",
	"E:/Learn/LearnOpenGL/SourceCode/skybox/front.jpg",
	"E:/Learn/LearnOpenGL/SourceCode/skybox/back.jpg",
};

Shader cuebmapShader("E:/Learn/LearnOpenGL/SourceCode/Cubemaps/Cubemap.vert",
	"E:/Learn/LearnOpenGL/SourceCode/Cubemaps/Cubemap.frag");
Shader cubeShader("E:/Learn/LearnOpenGL/SourceCode/Cubemaps/Cube.vert",
	"E:/Learn/LearnOpenGL/SourceCode/Cubemaps/Cube.frag");

void main()
{

	glEnable(GL_DEPTH_TEST);
	UpdateCubemap(cubemap, faces);
	UpdateTexture(cubeTex, "E:/Learn/LearnOpenGL/SourceCode/container.jpg",GL_REPEAT);
	UpdateVAOVBO_3Pos(skyboxVAO, skyboxVBO, CubeVertics_3Pos, sizeof(CubeVertics_3Pos));
	UpdateVAOVBO_3Pos_3Norm_2Texcoord(cubeVAO, cubeVBO, CubeVertices_3Pos_3Norm_2Texcoord, sizeof(CubeVertices_3Pos_3Norm_2Texcoord));

	window.SetRenderFunction(Render);
	window.MainLoop();

	glDepthFunc(GL_LEQUAL);
}

void Render()
{

	mat4 view = camera.GetViewMatrix();
	mat4 cubemapView = mat4(mat3(view));
	mat4 projection = perspective(camera.Zoom, (GLfloat)(window.windowWidth / window.windowHeight), 0.1f, 100.0f);


	cubeShader.Use();
	glBindVertexArray(cubeVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cubeTex);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
	glUniform3fv(glGetUniformLocation(cubeShader.Program, "camPos"), 1, value_ptr(camera.Position));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader.Program, "model"), 1, GL_FALSE, value_ptr(mat4()));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader.Program, "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader.Program, "projection"), 1, GL_FALSE, value_ptr(projection));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	cuebmapShader.Use();
	glBindVertexArray(skyboxVAO);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);
	glUniformMatrix4fv(glGetUniformLocation(cuebmapShader.Program, "view"), 1, GL_FALSE, value_ptr(cubemapView));
	glUniformMatrix4fv(glGetUniformLocation(cuebmapShader.Program, "projection"), 1, GL_FALSE, value_ptr(projection));
	glDrawArrays(GL_TRIANGLES, 0, 36);
}