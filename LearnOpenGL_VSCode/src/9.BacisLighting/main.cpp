
#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"

void UpdateHandle();

GO_Cube *coloredCube = nullptr;
GO_Cube *lamp = nullptr;
Scene scene(800, 600, "Basic Lighting");
GO_Camera *camera = nullptr;

int main()
{

    camera = new GO_Camera();
    scene.AddGameObject(camera);

    // Lamp
    vec3 lightColor = vec3(1, 1, 1);
    Shader *lightShader = new Shader("../Framework/Shaders/Default.vs", "./lamp.frag");
    lightShader->SetVec3("lightColor", lightColor);
    MeshRender *lightMeshRender = new MeshRender(lightShader);
    lamp = new GO_Cube(lightMeshRender);
    lamp->GetTransform()->SetPosition(vec3(0.5f, 0.3f, -0.8f));
    lamp->GetTransform()->SetScale(vec3(0.1f));
    scene.AddGameObject(lamp);

    // Colored Cube
    vec3 objectColor = vec3(1, 0, 0);
    Shader *cubeShader = new Shader("./object.vert", "./object.frag");
    cubeShader->SetFloat("ambientStrength", 0.1f);
    cubeShader->SetFloat("specularStrength", 0.5f);
    cubeShader->SetVec3("lightColor", lightColor)->SetVec3("objectColor", objectColor);
    MeshRender *coloredCubeMeshRender = new MeshRender(cubeShader);

    coloredCube = new GO_Cube(coloredCubeMeshRender);
    scene.AddGameObject(coloredCube);
    coloredCube->updateOperation = UpdateHandle;

    scene.MainLoop();
}

void UpdateHandle()
{
    vec3 cubePos = coloredCube->GetTransform()->GetPosition();
    Shader *cubeShader = coloredCube->GetMeshRender()->GetShader();
    cubeShader->SetVec3("lightPos", lamp->GetTransform()->GetPosition());
    lamp->GetTransform()->RotateAround(cubePos, vec3(0, 1, 0), scene.GetFrameTime() * 1.0f);

    cubeShader->SetVec3("viewPos", camera->GetTransform()->GetPosition());
}