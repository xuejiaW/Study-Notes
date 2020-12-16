#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/GameObjects/GO_Plane.h"
#include "../Framework/Mesh/Mesh_Screen.h"

Scene scene(1024, 1024, "Shadow Mapping");
GO_Camera *camera = new GO_Camera();

Shader *screenQuad = new Shader("../Framework/Shaders/Framebuffer.vs", "./debugDepth.fs"); // Used for render framebuffer to screen
Shader *drawDepthMapping = new Shader("../Framework/Shaders/DrawDepthMapping.vs", "../Framework/Shaders/DrawDepthMapping.fs");

Texture *woodTex = new Texture("../wood.png", true);

Material *woodMaterial = new Material(drawDepthMapping);
GO_Plane *floorObj = new GO_Plane(new MeshRender(woodMaterial));
GO_Cube *lamp = new GO_Cube();

bool usingBlinn = false;

GLuint framebuffer = -1;
GLuint texColorBuffer = -1;
GLuint texDepthStencilBuffer = -1;

GLuint depthMapFBO = -1;
GLuint texDepthMapDepthBuffer = -1;

MeshRender *depthMappingRender = new MeshRender(new Material(screenQuad));

void AddContent2Scene();
void CreateDepthMap();
void RenderDepthMap();

int main()
{
    depthMappingRender->SetMesh(new Mesh_Screen());

    CreateDepthMap();
    AddContent2Scene();

    scene.preRender = []() {
        glEnable(GL_DEPTH_TEST);
        scene.renderingDepthMap = true;

        drawDepthMapping->Use();
        // The model is setting by MeshRender
        glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
        glm::mat4 view = glm::lookAt(lamp->GetTransform()->GetPosition(), glm::vec3(0.0f), glm::vec3(0, 1, 0));
        drawDepthMapping->SetMat4("projection", projection)->SetMat4("view", view);

        glViewport(0, 0, 512, 512);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
    };

    scene.postRender = []() {
        glDisable(GL_DEPTH_TEST);
        scene.renderingDepthMap = false;
        glViewport(0, 0, 1024, 1024);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        depthMappingRender->DrawMesh();
    };
    scene.MainLoop();
}

void CreateDepthMap()
{
    glGenFramebuffers(1, &depthMapFBO);
    glGenTextures(1, &texDepthMapDepthBuffer);
    glBindTexture(GL_TEXTURE_2D, texDepthMapDepthBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 512, 512, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texDepthMapDepthBuffer, 0);
    glDrawBuffer(GL_NONE); // As the depth map framebuffer do not have color attachment, thus it is required to set draw/read buffer to null
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    depthMappingRender->GetShader()->Use();
    Texture *colorComponent = new Texture(texDepthMapDepthBuffer, scene.GetWidth(), scene.GetHeight());
    depthMappingRender->GetMaterial()->AddTexture("screenTexture", colorComponent);
}

void AddContent2Scene()
{
    scene.AddGameObject(camera);

    woodMaterial->AddTexture("floorTexture", woodTex);

    floorObj->GetTransform()->SetPosition(vec3(0, -3, 0));
    floorObj->GetTransform()->SetEulerAngle(vec3(-90, 0, 0));
    floorObj->GetTransform()->SetScale(vec3(5, 5, 5));
    scene.AddGameObject(floorObj);

    GO_Cube *go = new GO_Cube(new MeshRender(woodMaterial));
    scene.AddGameObject(go);

    lamp->GetTransform()->SetScale(vec3(0.1, 0.1, 0.1));
    lamp->GetTransform()->SetPosition(vec3(3, 1.2, 2));
    scene.AddGameObject(lamp);
}
