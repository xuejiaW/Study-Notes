#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/GameObjects/GO_Plane.h"
#include "../Framework/Mesh/Mesh_Screen.h"

Scene scene(800, 600, "Framebuffers");
GO_Camera *camera = nullptr;

void AddContentsToScene();
void CreateFrameBuffer();

GLuint framebuffer = -1;
GLuint texColorBuffer = -1;
GLuint texDepthStencilBuffer = -1;

MeshRender *screenMeshRender = new MeshRender(new Material(new Shader("./Framebuffer.vert", "./Framebuffer.frag")));

int main()
{
    screenMeshRender->SetMesh(new Mesh_Screen());

    CreateFrameBuffer();
    AddContentsToScene();

    // Bind framebuffer before rendering the screen
    scene.preRender = []() {
        glEnable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    };

    // Unbind framebuffer, and draw the framebuffer color component to default framebuffer
    scene.postRender = []() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        screenMeshRender->DrawMesh();
    };

    scene.MainLoop();
}

void CreateFrameBuffer()
{
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // Generate texture buffer
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, scene.GetWidth(), scene.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    // attach texture buffer to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

    // Bind color component to meshRender
    screenMeshRender->GetShader()->Use();
    Texture *colorComponent = new Texture(texColorBuffer, scene.GetWidth(), scene.GetHeight());
    screenMeshRender->GetMaterial()->AddTexture("screenTexture", colorComponent);

    // Genrerate depth and stencil Buffer using texture buffer
    // texDepthStencilBuffer = 0;
    // glGenTextures(1, &texDepthStencilBuffer);
    // glBindTexture(GL_TEXTURE_2D, texDepthStencilBuffer);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, scene.GetWidth(), scene.GetHeight(), 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glBindTexture(GL_TEXTURE_2D, 0);
    // // attach texture buffer to currently bound framebuffer object
    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texDepthStencilBuffer, 0);

    // Genrerate depth and stencil Buffer using rendering buffer object
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, scene.GetWidth(), scene.GetHeight());
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
    Shader *marbleShader = new Shader("../Framework/Shaders/Default.vs", "../Framework/Shaders/Texture.fs");

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