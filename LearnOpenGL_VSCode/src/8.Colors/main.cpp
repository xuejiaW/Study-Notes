#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/Mesh/Mesh_Cube.h"

int main()
{
    Scene scene(800, 600, "Color");

    GO_Camera *camera = new GO_Camera();
    scene.AddGameObject(camera);

    // Lamp
    vec3 lightColor = vec3(1, 1, 1);
    Shader *lightShader = new Shader("../Framework/Shaders/Default.vs", "./lamp.frag");
    lightShader->SetVec3("lightColor", lightColor);
    MeshRender *lightMeshRender = new MeshRender(lightShader);

    GO_Cube *lamp = new GO_Cube(lightMeshRender);
    lamp->GetTransform()->SetPosition(vec3(1.2f, 1.0f, -2.0f));
    scene.AddGameObject(lamp);

    // Colored Cube
    vec3 objectColor = vec3(0.2, 0, 0);
    Shader *cubeShader = new Shader("../Framework/Shaders/Default.vs", "./colorObject.frag");
    cubeShader->SetVec3("lightColor", lightColor)->SetVec3("objectColor", objectColor);
    MeshRender *coloredCubeMeshRender = new MeshRender(cubeShader);

    GO_Cube *coloredCube = new GO_Cube(coloredCubeMeshRender);
    scene.AddGameObject(coloredCube);

    scene.MainLoop();
}