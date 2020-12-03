#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/GameObjects/GO_Plane.h"
#include "../Framework/Mesh/Mesh_Screen.h"

Scene scene(800, 600, "AntiAliasing");
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

    glEnable(GL_MULTISAMPLE);

    // Bind framebuffer before rendering the screen
    scene.preRender = []() {
        glEnable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    };

    // Blit the multisample framebuffer to screen framebuffer(0)
    scene.postRender = []() {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, scene.GetWidth(), scene.GetHeight(), 0, 0, scene.GetWidth(), scene.GetHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    };

    scene.MainLoop();
}

void CreateFrameBuffer()
{
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // Generate texture buffer
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texColorBuffer);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, scene.GetWidth(), scene.GetHeight(), GL_TRUE);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    // attach texture buffer to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, texColorBuffer, 0);

    // Bind color component to meshRender
    screenMeshRender->GetShader()->Use();
    Texture *colorComponent = new Texture(texColorBuffer, scene.GetWidth(), scene.GetHeight());
    screenMeshRender->GetMaterial()->AddTexture("screenTexture", colorComponent);

    // Genrerate depth and stencil Buffer using rendering buffer object
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, scene.GetWidth(), scene.GetHeight());
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

    GO_Cube *marbleCube = new GO_Cube();
    marbleCube->GetTransform()->SetPosition(vec3(0.3, -0.1, 2));
    marbleCube->GetTransform()->SetEulerAngle(vec3(0, 30, 0));
    scene.AddGameObject(marbleCube);
}