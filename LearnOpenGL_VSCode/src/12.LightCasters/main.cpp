
#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"

void UpdateHandle();

GO_Cube *coloredCube[10]{nullptr};
GO_Cube *dirLight = nullptr;
GO_Cube *pointLight = nullptr;
Scene scene(800, 600, "LightingMaps");
GO_Camera *camera = nullptr;

glm::vec3 cubePositions[] = {
    glm::vec3(0.0f, 1.0f, -0.5f),
    glm::vec3(2.0f, 1.0f, -5.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f, 3.0f, -3.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f, 2.0f, -2.5f),
    glm::vec3(1.5f, 0.2f, -1.5f),
    glm::vec3(-1.3f, 1.0f, -1.5f)};

int main()
{

    camera = new GO_Camera();
    scene.AddGameObject(camera);

    // directional Light
    vec3 dirLightColor = vec3(1, 1, 1);
    vec3 dirLightPos = vec3(1.0f, 0.0f, 0.3f);
    Shader *lightShader = new Shader("../Framework/Shaders/Default.vertex", "./lamp.frag");
    lightShader->SetVec3("lightColor", dirLightColor);
    Material *lightMaterial = new Material(lightShader);
    MeshRender *dirLightMeshRender = new MeshRender(lightMaterial);

    dirLight = new GO_Cube(dirLightMeshRender);
    dirLight->GetTransform()->SetPosition(dirLightPos);
    dirLight->GetTransform()->SetScale(vec3(0.1f));
    scene.AddGameObject(dirLight);

    vec3 pointLightPos = vec3(1, 0.8, -2);
    MeshRender *pointLightMeshRender = new MeshRender(lightMaterial);
    pointLight = new GO_Cube(pointLightMeshRender);
    pointLight->GetTransform()->SetPosition(pointLightPos);
    pointLight->GetTransform()->SetScale(vec3(0.1f));
    scene.AddGameObject(pointLight);

    // Colored Cube
    Shader *cubeShader = new Shader("./object.vert", "./object.frag");
    Texture *diffuseMap = new Texture("../container.png");
    Texture *specularMap = new Texture("../container_specular.png");
    cubeShader->SetVec3("dirLight.direction", -dirLightPos);
    cubeShader->SetVec3("dirLight.ambient", vec3(0.05, 0.05, 0.05));
    cubeShader->SetVec3("dirLight.diffuse", vec3(0.4, 0.4, 0.4));
    cubeShader->SetVec3("dirLight.specular", vec3(0.5, 0.5, 0.5));

    cubeShader->SetVec3("pointLight.ambient", vec3(0.05, 0.05, 0.05));
    cubeShader->SetVec3("pointLight.diffuse", vec3(0.5, 0.5, 0.5));
    cubeShader->SetVec3("pointLight.specular", vec3(1, 1, 1));
    cubeShader->SetFloat("pointLight.constant", 1.0f);
    cubeShader->SetFloat("pointLight.linear", 0.09f);
    cubeShader->SetFloat("pointLight.quadratic", 0.32f);

    cubeShader->SetFloat("material.shininess", 32.0f);

    Material *cubeMaterial = new Material(cubeShader);
    cubeMaterial->AddTexture("material.diffuse", diffuseMap);   // will set material.diffuse
    cubeMaterial->AddTexture("material.specular", specularMap); // will set material.specular

    for (int i = 0; i != 10; ++i)
    {
        MeshRender *coloredCubeMeshRender = new MeshRender(cubeMaterial);

        coloredCube[i] = new GO_Cube(coloredCubeMeshRender);
        scene.AddGameObject(coloredCube[i]);
        coloredCube[i]->GetTransform()->SetPosition(cubePositions[i]);
    }

    scene.updateHandle = UpdateHandle;
    scene.MainLoop();
}

void UpdateHandle()
{
    vec3 cubePos = vec3(0, 0.8, 0);
    Shader *cubeShader = coloredCube[0]->GetMeshRender()->GetShader(); // Shared shader
    pointLight->GetTransform()->RotateAround(cubePos, vec3(0, 1, 0), scene.GetFrameTime() * 1.0f);
    cubeShader->SetVec3("pointLight.position", pointLight->GetTransform()->GetPosition());

    cubeShader->SetVec3("viewPos", camera->GetTransform()->GetPosition());
}