#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/GameObjects/GO_Plane.h"

Scene scene(800, 600, "StencilTesting");
GO_Camera *camera = nullptr;

void AddContentsToScene();
void CreateFrameBuffer();

GLuint framebuffer = -1;
GLuint texColorBuffer = -1;

float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
    // positions   // texCoords
    -1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 0.0f, 0.0f,
    1.0f, -1.0f, 1.0f, 0.0f,

    -1.0f, 1.0f, 0.0f, 1.0f,
    1.0f, -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 1.0f, 1.0f};

// screen quad VAO
unsigned int quadVAO, quadVBO;
Shader *screenShader = new Shader("./Framebuffer.vert", "./Framebuffer.frag");

int main()
{
    CreateFrameBuffer();

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));

    AddContentsToScene();
    scene.preRender = []() {
        glEnable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    };

    scene.postRender = []() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        screenShader->Use();
        glBindVertexArray(quadVAO);
        glDisable(GL_DEPTH_TEST);
        glBindTexture(GL_TEXTURE_2D, texColorBuffer);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    };

    scene.MainLoop();
}

void CreateFrameBuffer()
{
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // generate texture
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    // attach it to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

    // Depth and Stencil Buffer
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void AddContentsToScene()
{
    camera = new GO_Camera();
    scene.AddGameObject(camera);

    vec3 marbleCubePos[2] = {vec3{-0.3, 0, 0.5}, vec3{0.3, 0, -3}};

    Texture *marbleTex = new Texture("../marble.jpg");
    Shader *marbleShader = new Shader("../Framework/Shaders/Default.vertex", "../Framework/Shaders/Texture.frag");

    // Draw Plane
    GO_Plane *marblePlane = new GO_Plane(new MeshRender(marbleShader));
    marblePlane->GetMeshRender()->GetMaterial()->AddTexture("ourTexture", marbleTex);
    marblePlane->GetTransform()->SetScale(vec3(20, 20, 1));
    marblePlane->GetTransform()->SetPosition(vec3(0, -1, 0));
    marblePlane->GetTransform()->SetEulerAngle(vec3(-90, 0, 0));
    scene.AddGameObject(marblePlane);

    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    // Draw outlined cubes
    vec3 outlinedCubePos[2] = {vec3{-1.3, 0, -3}, vec3{1.3, 1, -5}};
    for (int i = 0; i != 2; ++i)
    {
        GO_Cube *redCube = new GO_Cube();
        redCube->GetTransform()->SetPosition(outlinedCubePos[i]);
        redCube->GetMeshRender()->GetMaterial()->SetColor(vec3(1, 0, 0));
        redCube->GetTransform()->SetScale(vec3(1, 1, 1));
        redCube->GetMeshRender()->SetPreRenderHandle([]() {
            glEnable(GL_STENCIL_TEST);
            glStencilMask(0xFF);
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
        });

        scene.AddGameObject(redCube);

        GO_Cube *redCube_2 = new GO_Cube();
        redCube_2->GetTransform()->SetPosition(outlinedCubePos[i]);
        redCube_2->GetMeshRender()->GetMaterial()->SetColor(vec3(1, 1, 0));
        redCube_2->GetTransform()->SetScale(vec3(1.05, 1.05, 1.05));
        redCube_2->GetMeshRender()->SetPreRenderHandle([]() {
            glStencilMask(0x00);
            glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
            glDisable(GL_DEPTH_TEST);
        });

        // Must turn on in post render or the clear process will not take effect
        redCube_2->GetMeshRender()->SetPostRenderHandle([]() {
            glEnable(GL_DEPTH_TEST);
            glStencilMask(0xFF);
            glDisable(GL_STENCIL_TEST);
        });
        scene.AddGameObject(redCube_2);
    }

    // Draw two cubes
    for (int i = 0; i != 2; ++i)
    {
        GO_Cube *marbleCube = new GO_Cube(new MeshRender(marbleShader));
        marbleCube->GetTransform()->SetPosition(marbleCubePos[i]);
        marbleCube->GetMeshRender()->GetMaterial()->AddTexture("ourTexture", marbleTex);
        marbleCube->GetTransform()->SetScale(vec3(1, 1, 1));
        scene.AddGameObject(marbleCube);
    }
}