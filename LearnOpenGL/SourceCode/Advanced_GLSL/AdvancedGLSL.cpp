#include <WINDOW.h>

Window window = Window("AdvancedGLSL",800, 600);

GLuint CubeTex, CubeVBO, CubeVAO;
Shader cubeShader = Shader("./Cube.vert",
	"./Cube.frag");
Shader cubeShader2 = Shader("./Cube.vert",
	"./Cube2.frag");

unsigned int uboMatrices;

void Render();
void main()
{
	UpdateTexture(CubeTex, "../container.jpg", GL_REPEAT);
	UpdateVAOVBO_3Pos_2Texcoord(CubeVAO, CubeVBO, cubeVertices_3Pos_2Texcoord, sizeof(cubeVertices_3Pos_2Texcoord));

	unsigned int uniformBlockIndexTex = glGetUniformBlockIndex(cubeShader.Program, "Matrices");
	unsigned int uniformBlockIndexRed = glGetUniformBlockIndex(cubeShader2.Program, "Matrices");
	glUniformBlockBinding(cubeShader.Program, uniformBlockIndexTex, 0);
	glUniformBlockBinding(cubeShader2.Program, uniformBlockIndexRed, 0);


	glGenBuffers(1, &uboMatrices);
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2*sizeof(mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(mat4));
	
	cubeShader.Use();

	mat4 projection = perspective(camera.Zoom, (GLfloat)(window.windowWidth / window.windowHeight), 0.1f, 100.0f);
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), value_ptr(projection));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glEnable(GL_DEPTH_TEST);
	window.SetRenderFunction(Render);
	window.MainLoop();
}

void Render()
{
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), value_ptr(camera.GetViewMatrix()));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindVertexArray(CubeVAO);

	cubeShader.Use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, CubeTex);
	glUniformMatrix4fv(glGetUniformLocation(cubeShader.Program, "model"), 1, GL_FALSE,value_ptr(mat4()));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	cubeShader2.Use();
	glUniformMatrix4fv(glGetUniformLocation(cubeShader.Program, "model"), 1, GL_FALSE, value_ptr(translate(mat4(),vec3(1.5,0.5,0))));
	glDrawArrays(GL_TRIANGLES, 0, 36);


	glBindVertexArray(0);
}