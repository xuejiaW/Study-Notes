#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"

Scene scene(800, 600, "StencilTesting");
GO_Camera *camera = nullptr;

int main()
{
    camera = new GO_Camera();
    scene.AddGameObject(camera);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    vec3 position[2] = {vec3{-0.3, 0, 0.5}, vec3{0.3, 1, -2}};

    for (int i = 0; i != 2; ++i)
    {
        GO_Cube *redCube = new GO_Cube();
        redCube->GetTransform()->SetPosition(position[i]);
        redCube->GetMeshRender()->GetMaterial()->SetColor(vec3(1, 0, 0));
        redCube->GetTransform()->SetScale(vec3(1, 1, 1));
        redCube->GetMeshRender()->SetPreRenderHandle([]() {
            glStencilMask(0xFF);
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
        });

        scene.AddGameObject(redCube);

        GO_Cube *redCube_2 = new GO_Cube();
        redCube_2->GetTransform()->SetPosition(position[i]);
        redCube_2->GetMeshRender()->GetMaterial()->SetColor(vec3(1, 1, 0));
        redCube_2->GetTransform()->SetScale(vec3(1.05, 1.05, 1.05));
        redCube_2->GetMeshRender()->SetPreRenderHandle([]() {
            glStencilMask(0x00);
            glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
            glDisable(GL_DEPTH_TEST);
        });

        // Must turn on in post render or the clear process will not take effect
        redCube_2->GetMeshRender()->SetPostRenderHandle([]() {
            glEnable(GL_DEPTH_TEST);
            glStencilMask(0xFF);
        });
        scene.AddGameObject(redCube_2);
    }

    scene.MainLoop();
}