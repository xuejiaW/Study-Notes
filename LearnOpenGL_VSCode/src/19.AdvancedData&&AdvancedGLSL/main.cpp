#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"

Scene scene(800, 600, "AdvancedData&&AdvancedGLSL");

GO_Camera *camera = new GO_Camera();

Shader *cubePointShader = new Shader("./pointRender.vert", "../Framework/Shaders/Default.fragment");
MeshRender *pointMeshRender = new MeshRender(cubePointShader);
GO_Cube *cube = new GO_Cube(pointMeshRender);

int main()
{
    glEnable(GL_PROGRAM_POINT_SIZE);

    scene.AddGameObject(camera);

    scene.AddGameObject(cube);
    cube->GetMeshRender()->SetDrawingMode(GL_POINTS);

    scene.MainLoop();
    return 0;
}