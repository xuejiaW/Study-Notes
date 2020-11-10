#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/GameObjects/GO_Plane.h"

Scene scene(800, 600, "FaceCulling");
GO_Camera *camera = nullptr;

int main()
{
    camera = new GO_Camera();
    scene.AddGameObject(camera);

    glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    glCullFace(GL_FRONT);
    // glCullFace(GL_FRONT_AND_BACK);

    // glFrontFace(GL_CCW);
    // glFrontFace(GL_CW);

    vec3 marbleCubePos[2] = {vec3{-0.3, 0, 0.5}, vec3{0.3, 0, -3}};

    Texture *marbleTex = new Texture("../marble.jpg");
    Shader *marbleShader = new Shader("../Framework/Shaders/Default.vertex", "../Framework/Shaders/Texture.frag");

    for (int i = 0; i != 2; ++i)
    {
        GO_Cube *marbleCube = new GO_Cube(new MeshRender(marbleShader));
        marbleCube->GetTransform()->SetPosition(marbleCubePos[i]);
        marbleCube->GetMeshRender()->GetMaterial()->AddTexture("ourTexture", marbleTex);
        marbleCube->GetTransform()->SetScale(vec3(1, 1, 1));
        scene.AddGameObject(marbleCube);
    }

    scene.MainLoop();
}