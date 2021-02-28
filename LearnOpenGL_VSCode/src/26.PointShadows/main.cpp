#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/GameObjects/GO_InverseCube.h"
#include "../Framework/GameObjects/GO_Plane.h"
#include "../Framework/Components/Cubemap.h"
#include "../Framework/Mesh/Mesh_Screen.h"

const int shadow_width = 1024, shadow_height = 1024;
const int screen_width = 1024, screen_height = 1024;

float aspect = (float)shadow_width / (float)shadow_height;
float near = 1.0f;
float far = 25.0f;
glm::mat4 shadowProject = glm::perspective(glm::radians(90.0f), aspect, near, far);
std::vector<glm::mat4> shadowTransforms;

Scene scene(screen_width, screen_height, "Shadow Mapping");
GO_Camera *camera = new GO_Camera();

Texture *woodTex = new Texture("../wood.png");

// Material *blinnShadowMaterial = new Material(new Shader("../Framework/Shaders/shadow.vs", "../Framework/Shaders/shadow.fs"));
Material *blinnShadowMaterial = new Material(new Shader("./PointShadow.vs", "./PointShadow.fs"));
Material *drawDepthMaterial = new Material(new Shader("./DrawDepthCubemap.vs", "./DrawDepthCubemap.fs", "./DrawDepthCubemap.gs"));

GLuint depthMapFBO = -1;
GLuint depthCubemap = -1;
Cubemap *depthMapCubemap = nullptr;

GO_Cube *lamp = new GO_Cube();
GO_InverseCube *homeBox = new GO_InverseCube();
GO_Cube **testBoxes = new GO_Cube *[9];

void AddContent2Scene();
void CreateDepthMap();
void RenderDepthMap();

int main()
{

    AddContent2Scene();
    CreateDepthMap();

    glm::vec3 lightPos = lamp->GetTransform()->GetPosition();
    shadowTransforms.push_back(shadowProject * glm::lookAt(lightPos, lightPos + glm::vec3(1, 0, 0), glm::vec3(0, -1, 0)));
    shadowTransforms.push_back(shadowProject * glm::lookAt(lightPos, lightPos + glm::vec3(-1, 0, 0), glm::vec3(0, -1, 0)));
    shadowTransforms.push_back(shadowProject * glm::lookAt(lightPos, lightPos + glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)));
    shadowTransforms.push_back(shadowProject * glm::lookAt(lightPos, lightPos + glm::vec3(0, -1, 0), glm::vec3(0, 0, 1)));
    shadowTransforms.push_back(shadowProject * glm::lookAt(lightPos, lightPos + glm::vec3(0, 0, 1), glm::vec3(0, -1, 0)));
    shadowTransforms.push_back(shadowProject * glm::lookAt(lightPos, lightPos + glm::vec3(0, 0, -1), glm::vec3(0, -1, 0)));

    scene.preRender = []() {
        scene.renderingDepthMap = true;
        homeBox->GetMeshRender()->SwitchMaterial(drawDepthMaterial);
        for (int i = 0; i != 9; ++i)
            testBoxes[i]->GetMeshRender()->SwitchMaterial(drawDepthMaterial);

        drawDepthMaterial->GetShader()->Use();
        for (int i = 0; i != 6; ++i)
            drawDepthMaterial->GetShader()->SetMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
        drawDepthMaterial->GetShader()->SetFloat("far_plane", far);
        drawDepthMaterial->GetShader()->SetVec3("lightPos", lamp->GetTransform()->GetPosition());

        glViewport(0, 0, shadow_width, shadow_height);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        scene.DrawFunc();

        glViewport(0, 0, screen_width, screen_height);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        scene.renderingDepthMap = false;

        blinnShadowMaterial->GetShader()->Use();
        blinnShadowMaterial->GetShader()->SetVec3("lightPos", lamp->GetTransform()->GetPosition());
        blinnShadowMaterial->GetShader()->SetVec3("viewPos", camera->GetTransform()->GetPosition());
        blinnShadowMaterial->GetShader()->SetFloat("far_plane", far);

        homeBox->GetMeshRender()->SwitchMaterial(blinnShadowMaterial);
        for (int i = 0; i != 9; ++i)
            testBoxes[i]->GetMeshRender()->SwitchMaterial(blinnShadowMaterial);
    };

    scene.MainLoop();
}

void CreateDepthMap()
{
    glGenTextures(1, &depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
    for (int i = 0; i != 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, shadow_width, shadow_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);

    glGenFramebuffers(1, &depthMapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
    glDrawBuffer(GL_NONE); // As the depth map framebuffer do not have color attachment, thus it is required to set draw/read buffer to null
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    depthMapCubemap = new Cubemap(depthCubemap);

    blinnShadowMaterial->GetShader()->Use();
    blinnShadowMaterial->AddTexture("diffuseTexture", woodTex);
    blinnShadowMaterial->AddTexture("depthMap", depthMapCubemap);
}

void AddContent2Scene()
{
    scene.AddGameObject(camera);
    camera->GetTransform()->SetPosition(vec3(0, 0, 2));

    homeBox->GetTransform()->SetScale(vec3(10, 10, 10));
    homeBox->GetMeshRender()->SwitchMaterial(blinnShadowMaterial);
    scene.AddGameObject(homeBox);

    for (int i = 0; i != 8; ++i)
    {
        testBoxes[i] = new GO_Cube();
        testBoxes[i]->GetMeshRender()->SwitchMaterial(blinnShadowMaterial);
        testBoxes[i]->GetTransform()->SetPosition(vec3(3 * (i % 2 == 0 ? 1 : -1), 3 * ((i / 2) % 2 == 0 ? 1 : -1), 3 * (i / 4 == 0 ? 1 : -1)));
        scene.AddGameObject(testBoxes[i]);
    }

    testBoxes[8] = new GO_Cube();
    testBoxes[8]->GetMeshRender()->SwitchMaterial(blinnShadowMaterial);
    testBoxes[8]->GetTransform()->SetPosition(vec3(0, 0, -3));
    scene.AddGameObject(testBoxes[8]);

    lamp->GetTransform()->SetScale(vec3(0.2, 0.2, 0.2));
    lamp->GetTransform()->SetPosition(vec3(1, -1, 0));
    scene.AddGameObject(lamp);
}
