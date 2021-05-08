#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_InverseCube.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/GameObjects/GO_Plane.h"
#include "../Framework/Mesh/Mesh_Screen.h"

Scene scene(800, 600, "Bloom");
GO_Camera *camera = new GO_Camera();

Texture *woodTex = new Texture("../wood.png", true);
Texture *containerTex = new Texture("../container.png", true);

MeshRender *screenMeshRender = new MeshRender(new Material(new Shader("./postProcessing.vs", "./finalOutput.fs")));
MeshRender *blurMeshRender = new MeshRender(new Material(new Shader("./postProcessing.vs", "./blur.fs")));

GO_Plane *floorObj = nullptr;
std::vector<GO_Cube *> lights;
std::vector<GO_Cube *> containers;

GLuint hdrFBO = -1;             // Scene will first render to this Framebuffer
GLuint colorBuffers[2]{-1, -1}; // Two floating point color, one for normal rendering, the other for brightness threshold values
GLuint depthStencilRBO = -1;

GLuint pingpongFBO[2]{-1, -1};          // Two framebuffer used for blue the brightness part
GLuint pingpongColorBuffers[2]{-1, -1}; // Two color buffers, one for each pingpongFBO

Texture *screenColor = nullptr;
Texture *brightColor = nullptr;
Texture *blurredBrightColor = nullptr;

Texture *pingpongColor[2]{nullptr, nullptr}; // Two Textures created by pingpongColorBuffers

void CreateFrameBuffer();
void AddSceneContent();

int main()
{
    screenMeshRender->SetMesh(new Mesh_Screen());
    blurMeshRender->SetMesh(new Mesh_Screen());

    AddSceneContent();
    CreateFrameBuffer();

    scene.preRender = []() {
        glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
        glClearColor(0.f, 0.f, 0.f, 1.0f); //HACK: Clear Color must be 0, otherwise it will be regarded as bright part
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    };

    scene.postRender = []() {
        bool horizontal = true;
        for (unsigned int i = 0; i != 10; ++i)
        {
            glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);

            blurMeshRender->GetMaterial()->GetShader()->SetInt("horizontal", horizontal);
            if (i == 0)
                blurMeshRender->GetMaterial()->SetTexture(0, brightColor);
            else
                blurMeshRender->GetMaterial()->SetTexture(0, pingpongColor[!horizontal]);
            blurMeshRender->DrawMesh();

            horizontal = !horizontal;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        screenMeshRender->DrawMesh();
    };

    scene.AddGameObject(camera);
    scene.MainLoop();
}

void AddSceneContent()
{
    Shader *objShader = new Shader("./objects.vs", "./objects.fs");
    // Add Floor
    MeshRender *floorMeshRender = new MeshRender(objShader);
    floorMeshRender->GetMaterial()->AddTexture("diffuseTexture", woodTex);
    floorObj = new GO_Plane(floorMeshRender);
    floorObj->GetTransform()->SetPosition(vec3(0, -3, 0));
    floorObj->GetTransform()->SetEulerAngle(vec3(-90, 0, 0));
    floorObj->GetTransform()->SetScale(vec3(20, 20, 5));
    scene.AddGameObject(floorObj);

    // Add Containers
    for (int i = 0; i != 5; ++i)
    {
        GO_Cube *container = new GO_Cube(new MeshRender(objShader));
        container->GetMeshRender()->GetMaterial()->AddTexture("diffuseTexture", containerTex);
        containers.push_back(container);
        scene.AddGameObject(container);
    }

    containers[0]->GetTransform()->SetPosition(vec3(0, 0, 0));
    containers[1]->GetTransform()->SetPosition(vec3(0.5, -0.3, 0.9));
    containers[2]->GetTransform()->SetPosition(vec3(-2, 0, 1.0));
    containers[3]->GetTransform()->SetPosition(vec3(0.3, 0.3, -0.5));
    containers[4]->GetTransform()->SetPosition(vec3(-0.7, 1, -1.0));

    // Adding Lights
    lights.push_back(new GO_Cube()); // White
    lights[0]->GetTransform()->SetPosition(vec3(-0.4, -0.1, 0.5f));
    lights[0]->GetMeshRender()->GetMaterial()->SetColor(vec3(3, 3, 3));

    lights.push_back(new GO_Cube()); // Red
    lights[1]->GetTransform()->SetPosition(vec3(-1.0f, 0.0f, 0.0f));
    lights[1]->GetMeshRender()->GetMaterial()->SetColor(vec3(0.1, 0, 0));

    lights.push_back(new GO_Cube()); // Green
    lights[2]->GetTransform()->SetPosition(vec3(0.8f, 1.0f, -0.3f));
    lights[2]->GetMeshRender()->GetMaterial()->SetColor(vec3(0.0, 0.1, 0));

    lights.push_back(new GO_Cube()); // Blue
    lights[3]->GetTransform()->SetPosition(vec3(0.5f, 0.5f, 0.3f));
    lights[3]->GetMeshRender()->GetMaterial()->SetColor(vec3(0.0, 0, 0.1));

    for (int i = 0; i != lights.size(); ++i)
    {
        lights[i]->GetTransform()->SetScale(vec3(0.15, 0.15, 0.15));
        scene.AddGameObject(lights[i]);

        // Set Light information to objects
        floorObj->GetMeshRender()->GetShader()->SetVec3("lights[" + std::to_string(i) + "].Position", lights[i]->GetTransform()->GetPosition());
        floorObj->GetMeshRender()->GetShader()->SetVec3("lights[" + std::to_string(i) + "].Color", lights[i]->GetMeshRender()->GetMaterial()->GetColor());

        for (int j = 0; j != containers.size(); ++j)
        {
            containers[j]->GetMeshRender()->GetShader()->SetVec3("lights[" + std::to_string(i) + "].Position", lights[i]->GetTransform()->GetPosition());
            containers[j]->GetMeshRender()->GetShader()->SetVec3("lights[" + std::to_string(i) + "].Color", lights[i]->GetMeshRender()->GetMaterial()->GetColor());
        }
    }
}

void CreateFrameBuffer()
{

    // For HDR framebuffer, which used to render scene
    // Creating two floating point color, one for normal rendering, the other for brightness threshold values
    glGenFramebuffers(1, &hdrFBO);
    glGenTextures(2, colorBuffers);

    glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
    for (int i = 0; i != 2; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, scene.GetWidth(), scene.GetHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
    }

    glGenRenderbuffers(1, &depthStencilRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, depthStencilRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, scene.GetWidth(), scene.GetHeight());
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencilRBO);

    unsigned int attachments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, attachments); // Tell OpenGL that this framebuffer needs draw two color attachment

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR:: HDR Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // For pingpong framebuffer, which used to blur the brightness from hdr framebuffer
    glGenFramebuffers(2, pingpongFBO);
    glGenTextures(2, pingpongColorBuffers);
    for (int i = 0; i != 2; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, pingpongColorBuffers[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, scene.GetWidth(), scene.GetHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Clamp to the edge as the blur filter would otherwise sample repeated texture values!
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorBuffers[i], 0);

        // There is no depth and stencil buffer bound, and the frame buffer is still complete
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR:: Pingpong Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    screenColor = new Texture(colorBuffers[0], scene.GetWidth(), scene.GetHeight());
    brightColor = new Texture(colorBuffers[1], scene.GetWidth(), scene.GetHeight());
    pingpongColor[0] = new Texture(pingpongColorBuffers[0], scene.GetWidth(), scene.GetHeight());
    pingpongColor[1] = new Texture(pingpongColorBuffers[1], scene.GetWidth(), scene.GetHeight());
    blurredBrightColor = new Texture(pingpongColorBuffers[0], scene.GetWidth(), scene.GetHeight());

    screenMeshRender->GetMaterial()->GetShader()->SetInt("usingBloom", 1);
    screenMeshRender->GetMaterial()->AddTexture("screenTexture", screenColor);

    // For Debug
    // screenMeshRender->GetMaterial()->GetShader()->SetInt("usingBloom", 0);
    // screenMeshRender->GetMaterial()->AddTexture("screenTexture", screenColor);
    // screenMeshRender->GetMaterial()->AddTexture("screenTexture", brightColor);
    // screenMeshRender->GetMaterial()->AddTexture("screenTexture", blurredBrightColor);

    screenMeshRender->GetMaterial()->AddTexture("blurredBrightColor", blurredBrightColor);
    blurMeshRender->GetMaterial()->AddTexture("brightColor", brightColor);
}
