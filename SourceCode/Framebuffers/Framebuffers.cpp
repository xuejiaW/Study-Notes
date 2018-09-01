#include <WINDOW.h>

using namespace std;
Window window("Framebuffers", 800, 600);

void Render();
GLuint CubeVBO, CubeVAO;
GLuint QuadVBO, QuadVAO;
GLuint CubeTex;
GLuint frameTexture, Depth_Stencil_Tex;
Shader shader("E:/Learn/LearnOpenGL/SourceCode/Framebuffers/Framebuffers.vert",
	"E:/Learn/LearnOpenGL/SourceCode/Framebuffers/framebuffers.frag");
Shader shader_screen("E:/Learn/LearnOpenGL/SourceCode/Framebuffers/screen.vert",
	"E:/Learn/LearnOpenGL/SourceCode/Framebuffers/screen.frag");

GLuint fbo;
GLuint rbo;

void main()
{
	UpdateVAOVBO_3Pos2Normal(CubeVAO, CubeVBO, cubeVertices, sizeof(cubeVertices));
	UpdateTexture(CubeTex, "E:/Learn/LearnOpenGL/SourceCode/container.jpg", GL_REPEAT);
	UpdateVAOVBO_3Pos2Normal(QuadVAO, QuadVBO, quadVertices, sizeof(quadVertices));

	UpdateTexture(frameTexture, NULL, 800, 600, GL_REPEAT);

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexture, 0);

	//Use Texture as depth and stencil
	glGenTextures(1, &Depth_Stencil_Tex);
	glBindTexture(GL_TEXTURE_2D, Depth_Stencil_Tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, Depth_Stencil_Tex, 0);

	////Use Renderbuffer as depth and stencil
	//glGenRenderbuffers(1, &rbo);
	//glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	//glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR: framebuffer not complete";
	glBindFramebuffer(GL_FRAMEBUFFER, 0);



	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	window.SetRenderFunction(Render);
	window.MainLoop();
}

void Render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glClearColor(0.1f, 0.1f, 0.1, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	mat4 view = camera.GetViewMatrix();
	mat4 projection = perspective(camera.Zoom, (GLfloat)(window.windowWidth / window.windowHeight), 0.1f, 100.0f);

	shader.Use();
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, value_ptr(projection));

	glBindVertexArray(CubeVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, CubeTex);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, value_ptr(mat4()));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindFramebuffer(GL_FRAMEBUFFER,0);
	shader_screen.Use();
	glClearColor(1, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, frameTexture);
	glBindVertexArray(QuadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

}