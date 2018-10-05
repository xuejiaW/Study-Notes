#include <WINDOW.h>;
#include <model.h>;
#include <mesh.h>;

Window window = Window("ModelEffect", 800, 600);

Shader shader_Exploding = Shader("E:/Learn/LearnOpenGL/SourceCode/ModelEffect/ModelEffect.vert",
	"E:/Learn/LearnOpenGL/SourceCode/ModelEffect/ModelEffect_Exploding.frag",
	"E:/Learn/LearnOpenGL/SourceCode/ModelEffect/ModelEffect_Exploding.geom");

Shader shader_VertexNormal = Shader("E:/Learn/LearnOpenGL/SourceCode/ModelEffect/ModelEffect.vert",
	"E:/Learn/LearnOpenGL/SourceCode/ModelEffect/ModelEffect_VertexNormal.frag",
	"E:/Learn/LearnOpenGL/SourceCode/ModelEffect/ModelEffect_VertexNormal.geom");

Shader shader_NoEffect = Shader("E:/Learn/LearnOpenGL/SourceCode/ModelEffect/ModelEffect.vert",
	"E:/Learn/LearnOpenGL/SourceCode/ModelEffect/ModelEffect.frag");

Model ourModel("E:/Learn/LearnOpenGL/SourceCode/Resource/nanoSuit/nanosuit.obj");

void Render();
GLuint uboMatrices;

void main() 
{
	GLuint uniformBlock_NoEffect = glGetUniformBlockIndex(shader_NoEffect.Program, "Matrices");
	GLuint uniformBlock_Exploding = glGetUniformBlockIndex(shader_Exploding.Program, "Matrices");
	GLuint uniformBlock_VertexNormal = glGetUniformBlockIndex(shader_VertexNormal.Program, "Matrices");
	glUniformBlockBinding(shader_NoEffect.Program, uniformBlock_NoEffect, 0);
	glUniformBlockBinding(shader_Exploding.Program, uniformBlock_Exploding, 0);
	glUniformBlockBinding(shader_VertexNormal.Program, uniformBlock_VertexNormal, 0);


	glGenBuffers(1, &uboMatrices);
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(mat4));

	glEnable(GL_DEPTH_TEST);
	window.SetRenderFunction(Render);
	window.MainLoop();
}

void Render()
{
	mat4 view = camera.GetViewMatrix();
	mat4 projection = perspective(camera.Zoom, (GLfloat)800 / 600, 0.1f, 100.0f);
	mat4 model = glm::translate(mat4(), glm::vec3(0.0f, -1.75f, 0.0f));// translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
	glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), value_ptr(view));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), value_ptr(projection));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	shader_NoEffect.Use();
	glUniformMatrix4fv(glGetUniformLocation(shader_NoEffect.Program, "model"), 1, GL_FALSE, value_ptr(model));
	ourModel.Draw(shader_NoEffect);

	shader_VertexNormal.Use();
	glUniformMatrix4fv(glGetUniformLocation(shader_VertexNormal.Program, "model"), 1, GL_FALSE, value_ptr(model));
	ourModel.Draw(shader_VertexNormal);

	shader_Exploding.Use();
	model = glm::translate(model, glm::vec3(10.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader_Exploding.Program, "model"), 1, GL_FALSE, value_ptr(model));
	glUniform1f(glGetUniformLocation(shader_Exploding.Program, "time"), glfwGetTime());
	ourModel.Draw(shader_Exploding);



}