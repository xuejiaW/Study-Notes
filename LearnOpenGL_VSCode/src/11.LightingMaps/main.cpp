
#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"

void UpdateHandle();

GO_Cube *coloredCube = nullptr;
GO_Cube *lamp = nullptr;
Scene scene(800, 600, "LightingMaps");
GO_Camera *camera = nullptr;

int main()
{

    camera = new GO_Camera();
    scene.AddGameObject(camera);

    // Lamp
    vec3 lightColor = vec3(1, 1, 1);
    Shader *lightShader = new Shader("../Framework/Shaders/Default.vertex", "./lamp.frag");
    lightShader->SetVec3("lightColor", lightColor);
    Material *lightMaterial = new Material(lightShader);
    MeshRender *lightMeshRender = new MeshRender(lightMaterial);

    lamp = new GO_Cube(lightMeshRender);
    lamp->GetTransform()->SetPosition(vec3(0.5f, 0.3f, -0.8f));
    lamp->GetTransform()->SetScale(vec3(0.1f));
    scene.AddGameObject(lamp);

    // Colored Cube
    Shader *cubeShader = new Shader("./object.vert", "./object.frag");
    Texture *diffuseMap = new Texture("../container.png");
    Texture *specularMap = new Texture("../container_specular.png");
    cubeShader->SetVec3("light.ambient", vec3(0.1, 0.1, 0.1));
    cubeShader->SetVec3("light.diffuse", vec3(0.5, 0.5, 0.5));
    cubeShader->SetVec3("light.specular", vec3(1.0, 1.0, 1.0));

    cubeShader->SetFloat("material.shiness", 32.0f);

    Material *cubeMaterial = new Material(cubeShader);
    cubeMaterial->AddTexture("material.diffuse", diffuseMap);
    cubeMaterial->AddTexture("material.specular", specularMap);
    MeshRender *coloredCubeMeshRender = new MeshRender(cubeMaterial);

    coloredCube = new GO_Cube(coloredCubeMeshRender);
    scene.AddGameObject(coloredCube);
    coloredCube->updateOperation = UpdateHandle;

    scene.MainLoop();
}

void UpdateHandle()
{
    vec3 cubePos = coloredCube->GetTransform()->GetPosition();
    Shader *cubeShader = coloredCube->GetMeshRender()->GetShader();
    cubeShader->SetVec3("light.position", lamp->GetTransform()->GetPosition());
    lamp->GetTransform()->RotateAround(cubePos, vec3(0, 1, 0), scene.GetFrameTime() * 1.0f);

    cubeShader->SetVec3("viewPos", camera->GetTransform()->GetPosition());
}