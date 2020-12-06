#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/GameObjects/GO_Plane.h"
#include "../Framework/Mesh/Mesh_Screen.h"

Scene scene(800, 600, "Gamma Correction");
GO_Camera *camera = new GO_Camera();

Texture *woodTex = new Texture("../wood.png");
Shader *floorShader = new Shader("./blinn-phone.vs", "./blinn-phone.fs");
Material *floorMaterial = new Material(floorShader);
MeshRender *floorMeshRender = new MeshRender(floorMaterial);
GO_Plane *floorObj = new GO_Plane(floorMeshRender);
GO_Cube *lamp = new GO_Cube();

bool usingBlinn = false;

GLuint framebuffer = -1;
GLuint texColorBuffer = -1;
GLuint texDepthStencilBuffer = -1;

MeshRender *screenMeshRender = new MeshRender(new Material(new Shader("./Framebuffer.vert", "./Framebuffer.frag")));

void CreateFrameBuffer();
void AddContent2Scene();

void UpdateHandle();
int main()
{
    screenMeshRender->SetMesh(new Mesh_Screen());

    CreateFrameBuffer();
    AddContent2Scene();

    scene.preRender = []() {
        // glDisable(GL_FRAMEBUFFER_SRGB);
        glEnable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    };

    // Unbind framebuffer, and draw the framebuffer color component to default framebuffer
    scene.postRender = []() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // glEnable(GL_FRAMEBUFFER_SRGB);
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

void AddContent2Scene()
{
    scene.updateHandle = UpdateHandle;
    scene.AddGameObject(camera);

    floorMaterial->AddTexture("floorTexture", woodTex);

    floorObj->GetTransform()->SetPosition(vec3(0, -3, 0));
    floorObj->GetTransform()->SetEulerAngle(vec3(-90, 0, 0));
    floorObj->GetTransform()->SetScale(vec3(5, 5, 5));
    scene.AddGameObject(floorObj);

    lamp->GetTransform()->SetPosition(vec3(0, 0, 1));
    scene.AddGameObject(lamp);
}

void UpdateHandle()
{
    floorShader->Use();
    floorShader->SetVec3("lightPos", lamp->GetTransform()->GetPosition());
    floorShader->SetVec3("viewPos", camera->GetTransform()->GetPosition());

    if (Input::GetInstance()->GetKeyDown(GLFW_KEY_B))
    {
        usingBlinn = !usingBlinn;
        Debug::Log(usingBlinn ? "Using Blinn" : "Not Using Blinn");
        floorShader->SetInt("blinn", usingBlinn);
    }
}
