#include <WINDOW.h>;
#include <model.h>;
#include <mesh.h>;

Window window = Window("ModelEffect", 800, 600);
Shader shader = Shader("E:/Learn/LearnOpenGL/SourceCode/ModelEffect/ModelEffect.vert",
	"E:/Learn/LearnOpenGL/SourceCode/ModelEffect/ModelEffect.frag",
	"E:/Learn/LearnOpenGL/SourceCode/ModelEffect/ModelEffect.geom");

//Shader shader = Shader("E:/Learn/LearnOpenGL/SourceCode/ModelEffect/ModelEffect.vert",
//	"E:/Learn/LearnOpenGL/SourceCode/ModelEffect/ModelEffect.frag");
Model ourModel("E:/Learn/LearnOpenGL/SourceCode/Model/nanoSuit/nanosuit.obj");

void Render();


void main() 
{
	glEnable(GL_DEPTH_TEST);
	window.SetRenderFunction(Render);
	window.MainLoop();
}

void Render()
{
	shader.Use();
	mat4 view = camera.GetViewMatrix();
	mat4 projection = perspective(camera.Zoom, (GLfloat)800/ 600, 0.1f, 100.0f);
	mat4 model= glm::translate(mat4(), glm::vec3(0.0f, -1.75f, 0.0f));// translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down

	glUniform1f(glGetUniformLocation(shader.Program, "time"), glfwGetTime());
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, value_ptr(projection));


	ourModel.Draw(shader);
}