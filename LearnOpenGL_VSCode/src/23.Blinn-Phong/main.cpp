#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/GameObjects/GO_Plane.h"
#include "../Framework/Mesh/Mesh_Screen.h"

Scene scene(800, 600, "Blinn-Phong");
GO_Camera *camera = new GO_Camera();

Texture *woodTex = new Texture("../wood.png");
Shader *floorShader = new Shader("./blinn-phone.vs", "./blinn-phone.fs");
Material *floorMaterial = new Material(floorShader);
MeshRender *floorMeshRender = new MeshRender(floorMaterial);
GO_Plane *floorObj = new GO_Plane(floorMeshRender);
GO_Cube *lamp = new GO_Cube();

bool usingBlinn = false;

void UpdateHandle();
int main()
{
    scene.updateHandle = UpdateHandle;
    scene.AddGameObject(camera);

    floorMaterial->AddTexture("floorTexture", woodTex);

    floorObj->GetTransform()->SetPosition(vec3(0, -3, 0));
    floorObj->GetTransform()->SetEulerAngle(vec3(-90, 0, 0));
    floorObj->GetTransform()->SetScale(vec3(5, 5, 5));
    scene.AddGameObject(floorObj);

    lamp->GetTransform()->SetPosition(vec3(0, 0, 1));
    scene.AddGameObject(lamp);

    scene.MainLoop();
}

void UpdateHandle()
{
    floorShader->Use();
    floorShader->SetVec3("lightPos", lamp->GetTransform()->GetPosition());
    floorShader->SetVec3("viewPos", camera->GetTransform()->GetPosition());

    if (Input::GetInstance()->GetKeyDown(GLFW_KEY_B))
    {
        usingBlinn = !usingBlinn;
        Debug::Log(usingBlinn ? "Using Blinn" : "Not Using Blinn");
        floorShader->SetInt("blinn", usingBlinn);
    }
}
