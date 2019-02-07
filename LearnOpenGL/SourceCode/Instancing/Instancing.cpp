#include <WINDOW.h>

Window window = Window("Instancing", 800, 600);
vec2 translations[100];

GLuint VAO, VBO,InstanceData;

void createTranslationsArray();
void Render();

Shader shader = Shader("E:/Learn/LearnOpenGL/SourceCode/Instancing/Instancing.vert",
	"E:/Learn/LearnOpenGL/SourceCode/Instancing/Instancing.frag");

void main()
{
	createTranslationsArray();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &InstanceData);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(smallQuadVertices_2Pos_3Color), smallQuadVertices_2Pos_3Color, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(2*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, InstanceData);
	glBufferData(GL_ARRAY_BUFFER, sizeof(translations), translations, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	window.SetRenderFunction(Render);
	window.MainLoop();
}

void Render()
{
	shader.Use();
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
}

void createTranslationsArray()
{
	int index = 0;
	float offset = 0.1f;
	for (int y = -10; y < 10; y += 2)
	{
		for (int x = -10; x < 10; x += 2)
		{
			glm::vec2 translation;
			translation.x = (float)x / 10.0f + offset;
			translation.y = (float)y / 10.0f + offset;
			translations[index++] = translation;
		}
	}
}