#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"

Scene scene(800, 600, "DepthTesting");
GO_Camera *camera = nullptr;

int main()
{
    camera = new GO_Camera();
    scene.AddGameObject(camera);

    GO_Cube *redCube = new GO_Cube();
    redCube->GetTransform()->SetPosition(vec3(-0.3, 0, 0.5));
    redCube->GetMeshRender()->GetMaterial()->SetColor(vec3(1, 0, 0));
    scene.AddGameObject(redCube);

    glDepthFunc(GL_ALWAYS);

    GO_Cube *greenCube = new GO_Cube();
    greenCube->GetMeshRender()->GetMaterial()->SetColor(vec3(0, 1, 0));
    scene.AddGameObject(greenCube);

    Shader *depthShader = new Shader("../Framework/Shaders/Default.vs", "./depthValue.frag");
    MeshRender *depthMeshRender = new MeshRender(depthShader);
    GO_Cube *depthCube = new GO_Cube(depthMeshRender);
    depthCube->GetTransform()->SetScale(vec3(2, 2, 2));
    depthCube->GetTransform()->SetPosition(vec3(2, 0, 0));
    depthCube->GetMeshRender()->GetMaterial()->SetColor(vec3(0, 1, 0));
    scene.AddGameObject(depthCube);

    scene.MainLoop();
}