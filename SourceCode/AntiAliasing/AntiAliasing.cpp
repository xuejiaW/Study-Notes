#include <WINDOW.h>

Window window = Window("AntiAliasing", 800, 600);
Shader cubeShader = Shader("E:/Learn/LearnOpenGL/SourceCode/AntiAliasing/Cube.vert",
	"E:/Learn/LearnOpenGL/SourceCode/AntiAliasing/Cube.frag");
Shader screenShader = Shader("E:/Learn/LearnOpenGL/SourceCode/AntiAliasing/Screen.vert",
	"E:/Learn/LearnOpenGL/SourceCode/AntiAliasing/Screen.frag");

GLuint cubeTex,multisampleFrameTex,intermediateFrameTex;
GLuint CubeVBO, CubeVAO;
GLuint QuadVBO, QuadVAO;
GLuint multisampleFbo, intermediateFBO,rbo;

void Render();

void main()
{
	UpdateVAOVBO_3Pos_2Texcoord(CubeVAO, CubeVBO, cubeVertices_3Pos_2Texcoord, sizeof(cubeVertices_3Pos_2Texcoord));
	UpdateVAOVBO_3Pos_2Texcoord(QuadVAO, QuadVBO, quadVertices_3Pos_2Texcoord, sizeof(quadVertices_3Pos_2Texcoord));

	UpdateTexture(cubeTex, "E:/Learn/LearnOpenGL/SourceCode/container.jpg", GL_REPEAT);
	UpdateMultiSampleTexture(multisampleFrameTex, NULL, 800, 600, GL_REPEAT);
	UpdateTexture(intermediateFrameTex, NULL, 800, 600, GL_REPEAT);

	glGenFramebuffers(1, &multisampleFbo);
	glBindFramebuffer(GL_FRAMEBUFFER, multisampleFbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D_MULTISAMPLE, multisampleFrameTex, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER,4, GL_DEPTH24_STENCIL8, 800, 600);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR: framebuffer not complete";
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glGenFramebuffers(1, &intermediateFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, intermediateFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, intermediateFrameTex, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR: framebuffer22  not complete";
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	window.SetRenderFunction(Render);
	window.MainLoop();
}

void Render()
{
	glBindFramebuffer(GL_FRAMEBUFFER, multisampleFbo);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cubeShader.Use();
	glEnable(GL_DEPTH_TEST);
	mat4 view = camera.GetViewMatrix();
	mat4 projection = perspective(camera.Zoom, (GLfloat)(window.windowWidth / window.windowHeight), 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(cubeShader.Program, "view"), 1, GL_FALSE, value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader.Program, "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader.Program, "model"), 1, GL_FALSE, value_ptr(mat4()));

	glBindVertexArray(CubeVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cubeTex);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	
	//Directly blit to the default framebuffer(screen)
	glBindFramebuffer(GL_READ_FRAMEBUFFER, multisampleFbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, 800, 600, 0, 0, 800, 600, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	

	
	////Use the intermediate framebuffer
	//glBindFramebuffer(GL_READ_FRAMEBUFFER, multisampleFbo);
	//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFBO);
	//glBlitFramebuffer(0, 0, 800, 600, 0, 0, 800, 600, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//screenShader.Use();
	//glClearColor(1, 1, 0, 1);
	//glClear(GL_COLOR_BUFFER_BIT);
	//glDisable(GL_DEPTH_TEST);
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, intermediateFrameTex);
	//glBindVertexArray(QuadVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 6);

}