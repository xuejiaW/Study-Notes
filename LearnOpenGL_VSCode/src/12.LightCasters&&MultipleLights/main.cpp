#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"

void UpdateHandle();

GO_Cube *coloredCube[10]{nullptr};
GO_Cube *dirLight = nullptr;
GO_Cube *pointLight[2]{nullptr};
Scene scene(800, 600, "LightCasters&&MultipleLights");
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

glm::vec3 pointLightPositions[] = {
    glm::vec3(1, 0.8, -2),
    glm::vec3(-1, -0., -2)};

int main()
{

    camera = new GO_Camera();
    scene.AddGameObject(camera);

    // directional Light
    vec3 dirLightColor = vec3(1, 1, 1);
    vec3 dirLightPos = vec3(1.0f, 0.0f, 0.3f);
    Shader *lightShader = new Shader("../Framework/Shaders/Default.vs", "./lamp.frag");
    lightShader->SetVec3("lightColor", dirLightColor);
    Material *lightMaterial = new Material(lightShader);
    MeshRender *dirLightMeshRender = new MeshRender(lightMaterial);

    dirLight = new GO_Cube(dirLightMeshRender);
    dirLight->GetTransform()->SetPosition(dirLightPos);
    dirLight->GetTransform()->SetScale(vec3(0.1f));
    scene.AddGameObject(dirLight);

    for (int i = 0; i != 2; ++i)
    {
        MeshRender *pointLightMeshRender = new MeshRender(lightMaterial);
        pointLight[i] = new GO_Cube(pointLightMeshRender);
        pointLight[i]->GetTransform()->SetPosition(pointLightPositions[i]);
        pointLight[i]->GetTransform()->SetScale(vec3(0.1f));
        scene.AddGameObject(pointLight[i]);
    }

    // Colored Cube
    Shader *cubeShader = new Shader("./object.vert", "./object.frag");
    Texture *diffuseMap = new Texture("../container.png");
    Texture *specularMap = new Texture("../container_specular.png");

    // Setting for material
    Material *cubeMaterial = new Material(cubeShader);
    cubeShader->SetFloat("material.shininess", 32.0f);
    cubeMaterial->AddTexture("material.diffuse", diffuseMap);   // will set material.diffuse
    cubeMaterial->AddTexture("material.specular", specularMap); // will set material.specular

    cubeShader->SetVec3("ambient", vec3(0.05, 0.05, 0.05));

    // Setting for directional Light
    cubeShader->SetVec3("dirLight.direction", -dirLightPos);
    cubeShader->SetVec3("dirLight.diffuse", vec3(0.2, 0.2, 0.2));
    cubeShader->SetVec3("dirLight.specular", vec3(0.3, 0.3, 0.3));

    // Setting for point Lights
    for (int i = 0; i != 2; ++i)
    {
        cubeShader->SetVec3("pointLights[" + to_string(i) + "].diffuse", vec3(0.5, 0.5, 0.5));
        cubeShader->SetVec3("pointLights[" + to_string(i) + "].specular", vec3(1, 1, 1));
        cubeShader->SetFloat("pointLights[" + to_string(i) + "].constant", 1.0f);
        cubeShader->SetFloat("pointLights[" + to_string(i) + "].linear", 0.09f);
        cubeShader->SetFloat("pointLights[" + to_string(i) + "].quadratic", 0.032f);
    }

    // Setting for Spot Lights
    cubeShader->SetVec3("spotLight.diffuse", vec3(1, 1, 1));
    cubeShader->SetVec3("spotLight.specular", vec3(1, 1, 1));
    cubeShader->SetFloat("spotLight.constant", 1.0f);
    cubeShader->SetFloat("spotLight.linear", 0.09);
    cubeShader->SetFloat("spotLight.quadratic", 0.032);
    cubeShader->SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    cubeShader->SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

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
    pointLight[0]->GetTransform()->RotateAround(cubePos, vec3(0, 1, -2), scene.GetFrameTime() * 1.0f);
    cubeShader->SetVec3("pointLights[0].position", pointLight[0]->GetTransform()->GetPosition());

    pointLight[1]->GetTransform()->RotateAround(cubePos, vec3(1, 0, -2), scene.GetFrameTime() * 1.0f);
    cubeShader->SetVec3("pointLights[1].position", pointLight[1]->GetTransform()->GetPosition());

    Camera *camera = scene.GetMainCamera();

    cubeShader->SetVec3("viewPos", camera->GetPosition());
    cubeShader->SetVec3("spotLight.position", camera->GetPosition());
    cubeShader->SetVec3("spotLight.direction", camera->GetForward());
}