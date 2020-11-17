#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/Components/Texture.h"

Scene scene(800, 600, "AdvancedData&&AdvancedGLSL");

GO_Camera *camera = new GO_Camera();

Shader *cubePointShader = new Shader("./pointRender.vert", "../Framework/Shaders/Default.fragment");
MeshRender *pointMeshRender = new MeshRender(cubePointShader);
GO_Cube *pointCube = new GO_Cube(pointMeshRender);

Shader *halfShader = new Shader("../Framework/Shaders/Default.vertex", "./half.frag");
GO_Cube *halfCube = new GO_Cube(new MeshRender(halfShader));

Shader *frontFacingShader = new Shader("./interfaceBlock.vert", "./frontFacing.frag");
GO_Cube *frontFacingCube = new GO_Cube(new MeshRender(frontFacingShader));

Texture *frontTexture = new Texture("../marble.jpg");
Texture *backTexture = new Texture("../container.jpg");

int main()
{
    glEnable(GL_PROGRAM_POINT_SIZE);

    scene.AddGameObject(camera);

    pointCube->GetMeshRender()->SetDrawingMode(GL_POINTS);
    scene.AddGameObject(pointCube);

    halfCube->GetTransform()->SetPosition(vec3(1, 0, 0));
    scene.AddGameObject(halfCube);

    frontFacingCube->GetMeshRender()->GetMaterial()->AddTexture("frontTexture", frontTexture);
    frontFacingCube->GetMeshRender()->GetMaterial()->AddTexture("backTexture", backTexture);
    frontFacingCube->GetTransform()->SetPosition(vec3(-1, 0, 0));
    scene.AddGameObject(frontFacingCube);

    scene.MainLoop();
    return 0;
}