#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/GameObjects/GO_Plane.h"

Scene scene(800, 600, "Blending");
GO_Camera *camera = nullptr;

int main()
{
    camera = new GO_Camera();
    scene.AddGameObject(camera);

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

    GO_Plane *marblePlane = new GO_Plane(new MeshRender(marbleShader));
    marblePlane->GetMeshRender()->GetMaterial()->AddTexture("ourTexture", marbleTex);
    marblePlane->GetTransform()->SetScale(vec3(20, 20, 1));
    marblePlane->GetTransform()->SetPosition(vec3(0, -1, 0));
    marblePlane->GetTransform()->SetEulerAngle(vec3(-90, 0, 0));
    scene.AddGameObject(marblePlane);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    vec3 grassPos[2] = {vec3{-0.5, 0, 2}, {0.7, 0, -2.5}};
    Texture *grassTex = new Texture("../grass.png");
    grassTex->SetWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    Shader *grassShader = new Shader("../Framework/Shaders/Default.vertex", "./Grass.frag");

    for (int i = 0; i != 2; ++i)
    {
        GO_Plane *grass = new GO_Plane(new MeshRender(grassShader));
        grass->GetTransform()->SetPosition(grassPos[i]);
        grass->GetMeshRender()->GetMaterial()->AddTexture("ourTexture", grassTex);
        grass->GetTransform()->SetScale(vec3(1, 1, 1));
        scene.AddGameObject(grass);
    }

    Shader *windowShader = new Shader("../Framework/Shaders/Default.vertex", "../Framework/Shaders/Texture.frag");
    Texture *windowTex = new Texture("../blending_transparent_window.png");
    vec3 windowPos[3] = {{1.5, 0, -2}, {-1.0, 0, 1}, {-1.5, 0, 1.5}};
    for (int i = 0; i != 3; ++i)
    {
        GO_Plane *window = new GO_Plane(new MeshRender(windowShader));
        window->GetTransform()->SetPosition(windowPos[i]);
        window->GetMeshRender()->GetMaterial()->AddTexture("ourTexture", windowTex);
        window->GetTransform()->SetScale(vec3(1, 1, 1));
        scene.AddGameObject(window);
    }

    scene.MainLoop();
}