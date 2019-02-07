#include <WINDOW.h>

Window window = Window("Geometry", 800, 600);
Shader shader = Shader("E:/Learn/LearnOpenGL/SourceCode/GeometryShader/Point.vert"
	, "E:/Learn/LearnOpenGL/SourceCode/GeometryShader/Point.frag",
	"E:/Learn/LearnOpenGL/SourceCode/GeometryShader/Point.geom");


float points[] =
{
	-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // 左上
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // 右上
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // 右下
	-0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // 左下
};

GLuint pointVAO, pointVBO;
void Render();

void main()
{
	glGenVertexArrays(1, &pointVAO);
	glGenBuffers(1, &pointVBO);
	glBindVertexArray(pointVAO);
	glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,5 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GL_FLOAT), (GLvoid*)(2*sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	window.SetRenderFunction(Render);
	window.MainLoop();
}

void Render()
{
	glBindVertexArray(pointVAO);
	shader.Use();
	glDrawArrays(GL_POINTS, 0, 4);
}