#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_InverseCube.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/GameObjects/GO_Plane.h"
#include "../Framework/Mesh/Mesh_Screen.h"

Scene scene(800, 600, "HDR");
GO_Camera *camera = new GO_Camera();

Texture *woodTex = new Texture("../wood.png", true);
MeshRender *tunnelMeshRender = new MeshRender(new Shader("./tunnel.vs", "./tunnel.fs"));
MeshRender *screenMeshRender = new MeshRender(new Material(new Shader("./hdr.vs", "./hdr.fs")));

GO_InverseCube *tunnel = new GO_InverseCube(tunnelMeshRender);

std::vector<GO_Cube *> lights;

GLuint hdrFBO = -1;
GLuint texColorBuffer = -1;
GLuint texDepthStencilBuffer = -1;

void CreateFrameBuffer();

int main()
{
    screenMeshRender->SetMesh(new Mesh_Screen());

    CreateFrameBuffer();
    lights.push_back(new GO_Cube());
    lights[0]->GetTransform()->SetPosition(vec3(0, 0, -11.0f));
    lights[0]->GetMeshRender()->GetMaterial()->SetColor(vec3(100, 100, 100));

    lights.push_back(new GO_Cube());
    lights[1]->GetTransform()->SetPosition(vec3(-1.0f, -0.8f, -1.0f));
    lights[1]->GetMeshRender()->GetMaterial()->SetColor(vec3(0.1, 0, 0));

    lights.push_back(new GO_Cube());
    lights[2]->GetTransform()->SetPosition(vec3(0.8f, 0.5f, -1.0f));
    lights[2]->GetMeshRender()->GetMaterial()->SetColor(vec3(0.0, 0.1, 0));

    lights.push_back(new GO_Cube());
    lights[3]->GetTransform()->SetPosition(vec3(0.0f, -1.0f, -1.0f));
    lights[3]->GetMeshRender()->GetMaterial()->SetColor(vec3(0.0, 0, 0.1));

    tunnel->GetTransform()->SetScale(vec3(2.5f, 2.5f, 24.0f));
    tunnel->GetMeshRender()->GetMaterial()->AddTexture("diffuseTexture", woodTex);

    for (int i = 0; i != lights.size(); ++i)
    {
        lights[i]->GetTransform()->SetScale(vec3(0.1, 0.1, 0.1));

        scene.AddGameObject(lights[i]);
        tunnel->GetMeshRender()->GetShader()->SetVec3("lights[" + std::to_string(i) + "].Position", lights[i]->GetTransform()->GetPosition());
        tunnel->GetMeshRender()->GetShader()->SetVec3("lights[" + std::to_string(i) + "].Color", lights[i]->GetMeshRender()->GetMaterial()->GetColor());
    }

    scene.preRender = []() {
        tunnel->GetMeshRender()->GetShader()->SetVec3("viewPose", camera->GetTransform()->GetPosition());

        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    };

    scene.postRender = []() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        screenMeshRender->DrawMesh();
    };

    scene.AddGameObject(camera);
    scene.AddGameObject(tunnel);

    scene.MainLoop();
}

void CreateFrameBuffer()
{
    glGenFramebuffers(1, &hdrFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);

    // Creating Floating Point color attachment and binding
    glGenTextures(1, &texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, scene.GetWidth(), scene.GetHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, scene.GetWidth(), scene.GetHeight());
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    Texture *colorComponent = new Texture(texColorBuffer, scene.GetWidth(), scene.GetHeight());
    screenMeshRender->GetMaterial()->AddTexture("screenTexture", colorComponent);
}