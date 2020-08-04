#include "Engine.h"
#include "SHADER.h"
#include <direct.h>

void init();

void loop();

Engine *engine;

int main()
{
	engine = new Engine(800, 600);
	engine->SetInitFunc(&init);
	engine->SetMainLoop(&loop);
	engine->Run();
	return 0;
}

GLuint VAO, VBO;
void init()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	cout << "init" << endl;
}

void loop()
{
	Shader shader("./src/Cube.vert", "./src/Cube.frag");
	shader.Use();

	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection;
	GLint width, height;

	glfwGetFramebufferSize(engine->window, &width, &height);
	projection = glm::perspective(glm::radians(fov), (GLfloat)width / height, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(VAO);
	for (int i = 0; i < 10; ++i)
	{
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(48.0f) * i, glm::vec3(0, 1, 0));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);

	glfwSwapBuffers(engine->window);

	// cout << "loop" << endl;
}