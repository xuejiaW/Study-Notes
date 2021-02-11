#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/GameObjects/GO_Plane.h"
#include "../Framework/Mesh/Mesh_Screen.h"

Scene scene(1024, 1024, "Shadow Mapping");
GO_Camera *camera = new GO_Camera();

Shader *screenQuad = new Shader("../Framework/Shaders/Framebuffer.vs", "./debugDepth.fs"); // Used for render framebuffer to screen
Shader *drawDepthMapShader = new Shader("../Framework/Shaders/DrawDepthMapping.vs", "../Framework/Shaders/DrawDepthMapping.fs");
Shader *blinnShadowShader = new Shader("../Framework/Shaders/shadow.vs", "../Framework/Shaders/shadow.fs");

Texture *woodTex = new Texture("../wood.png", true);

Material *drawDepthMaterial = new Material(drawDepthMapShader);
Material *blinnShadowMaterial = new Material(blinnShadowShader);

bool usingBlinn = false;

GLuint framebuffer = -1;
GLuint texColorBuffer = -1;
GLuint texDepthStencilBuffer = -1;

GLuint depthMapFBO = -1;
GLuint texDepthMapDepthBuffer = -1;
Texture *depthMapTexture = nullptr;

MeshRender *depthQuadRender = new MeshRender(new Material(screenQuad));

GO_Cube *lamp = new GO_Cube();
GO_Plane *floorObj = new GO_Plane(new MeshRender(drawDepthMaterial));
GO_Cube *go = new GO_Cube(new MeshRender(drawDepthMaterial));

void AddContent2Scene();
void CreateDepthMap();
void RenderDepthMap();

int main()
{
    depthQuadRender->SetMesh(new Mesh_Screen());
    glEnable(GL_CULL_FACE);
    AddContent2Scene();
    CreateDepthMap();

    scene.preRender = []() {
        // glEnable(GL_DEPTH_TEST);
        scene.renderingDepthMap = true;
        // glCullFace(GL_FRONT);
        // Switch to the drawDepthMaterial to render depth
        go->GetMeshRender()->SwitchMaterial(drawDepthMaterial);
        floorObj->GetMeshRender()->SwitchMaterial(drawDepthMaterial);

        drawDepthMapShader->Use();
        // The model is setting by MeshRender
        glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 7.5f);
        glm::mat4 view = glm::lookAt(lamp->GetTransform()->GetPosition(), glm::vec3(0.0f), glm::vec3(0, 1, 0));

        drawDepthMapShader->SetMat4("projection", projection)->SetMat4("view", view);

        glViewport(0, 0, 512, 512);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        scene.DrawFunc(); // To Generate Depth Map

        // Normally render the scene
        glFlush();
        glViewport(0, 0, 1024, 1024);
        // glCullFace(GL_BACK);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        scene.renderingDepthMap = false;

        blinnShadowShader->Use();
        blinnShadowShader->SetMat4("lightSpaceMatrix", projection * view);
        blinnShadowShader->SetVec3("lightPos", lamp->GetTransform()->GetPosition());
        blinnShadowShader->SetVec3("viewPos", camera->GetTransform()->GetPosition());
        // Switch to the normal material to render the scene
        go->GetMeshRender()->SwitchMaterial(blinnShadowMaterial);
        floorObj->GetMeshRender()->SwitchMaterial(blinnShadowMaterial);
    };

    scene.postRender = []() {
        // glViewport(0, 0, 1024, 1024);
        // glCullFace(GL_BACK);
        // glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // depthQuadRender->DrawMesh();
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

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    float borderColor[]{1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texDepthMapDepthBuffer, 0);
    glDrawBuffer(GL_NONE); // As the depth map framebuffer do not have color attachment, thus it is required to set draw/read buffer to null
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    depthMapTexture = new Texture(texDepthMapDepthBuffer, scene.GetWidth(), scene.GetHeight());
    depthQuadRender->GetShader()->Use();
    depthQuadRender->GetMaterial()->AddTexture("screenTexture", depthMapTexture);

    blinnShadowShader->Use();
    blinnShadowMaterial->AddTexture("diffuseTexture", woodTex);
    blinnShadowMaterial->AddTexture("depthMap", depthMapTexture);
}

void AddContent2Scene()
{
    scene.AddGameObject(camera);

    floorObj->GetTransform()->SetPosition(vec3(0, -3, 0));
    floorObj->GetTransform()->SetEulerAngle(vec3(-90, 0, 0));
    floorObj->GetTransform()->SetScale(vec3(20, 20, 5));
    scene.AddGameObject(floorObj);

    scene.AddGameObject(go);

    lamp->GetTransform()->SetScale(vec3(0.1, 0.1, 0.1));
    lamp->GetTransform()->SetPosition(vec3(3, 5, 2));
    scene.AddGameObject(lamp);
}
