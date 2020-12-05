#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/GameObjects/GO_Plane.h"
#include "../Framework/Mesh/Mesh_Screen.h"

Scene scene(800, 600, "AntiAliasing");
GO_Camera *camera = nullptr;

void AddContentsToScene();
void CreateMultiSampleFrameBuffer();
void CreateIntermediateFrameBuffer();

GLuint multisampledFramebuffer = -1;
GLuint intermediateFramebuffer = -1;
GLuint multisampledTexture = -1;
GLuint screenTexture = -1;
GLuint texDepthStencilBuffer = -1;

MeshRender *screenMeshRender = new MeshRender(new Material(new Shader("./Framebuffer.vert", "./Framebuffer.frag")));

int main()
{
    screenMeshRender->SetMesh(new Mesh_Screen());

    CreateMultiSampleFrameBuffer();
    CreateIntermediateFrameBuffer();
    AddContentsToScene();

    glEnable(GL_MULTISAMPLE);

    // Bind framebuffer before rendering the screen
    scene.preRender = []() {
        glEnable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER, multisampledFramebuffer);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    };

    scene.postRender = []() {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, multisampledFramebuffer);

        // // Blit the multisample framebuffer to screen framebuffer(0)
        // glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        // glBlitFramebuffer(0, 0, scene.GetWidth(), scene.GetHeight(), 0, 0, scene.GetWidth(), scene.GetHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);

        // Blit the multiSampled framebuffer to intermediateFramebuffer
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFramebuffer);
        glBlitFramebuffer(0, 0, scene.GetWidth(), scene.GetHeight(), 0, 0, scene.GetWidth(), scene.GetHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        screenMeshRender->DrawMesh();
    };

    scene.MainLoop();
}

void CreateMultiSampleFrameBuffer()
{
    glGenFramebuffers(1, &multisampledFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, multisampledFramebuffer);

    // Generate texture buffer
    glGenTextures(1, &multisampledTexture);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, multisampledTexture);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, scene.GetWidth(), scene.GetHeight(), GL_TRUE);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    // attach texture buffer to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, multisampledTexture, 0);

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

void CreateIntermediateFrameBuffer()
{
    glGenFramebuffers(1, &intermediateFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, intermediateFramebuffer);

    // Generate texture buffer
    glGenTextures(1, &screenTexture);
    glBindTexture(GL_TEXTURE_2D, screenTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, scene.GetWidth(), scene.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    // attach texture buffer to currently bound framebuffer object
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, screenTexture, 0);

    // Bind color component to meshRender
    screenMeshRender->GetShader()->Use();
    Texture *colorComponent = new Texture(screenTexture, scene.GetWidth(), scene.GetHeight());
    screenMeshRender->GetMaterial()->AddTexture("screenTexture", colorComponent);
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