#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Plane.h"
#include "../Framework/GameObjects/GO_Quad_TBN.h"
#include "../Framework/GameObjects/GO_Cube.h"

const int screen_width = 1024, screen_height = 1024;

Scene scene(screen_width, screen_height, "Parallax Mapping");
GO_Camera *camera = new GO_Camera();

MeshRender *planeMeshRender = new MeshRender(new Material("./parallaxMapping.vs", "./parallaxMapping.fs"));
GO_Quad_TBN *plane = new GO_Quad_TBN(planeMeshRender);
GO_Cube *lamp = new GO_Cube();

Texture *brickDiffuse = new Texture("./BrickDiffuse.jpg");
Texture *brickNormal = new Texture("./BrickNormal.jpg");
Texture *brickDisplacement = new Texture("./BrickDisplacement.jpg");

int main()
{
    plane->GetMeshRender()->GetMaterial()->AddTexture("diffuseTexture", brickDiffuse);
    plane->GetMeshRender()->GetMaterial()->AddTexture("normalMap", brickNormal);
    plane->GetMeshRender()->GetMaterial()->AddTexture("displacementMap", brickDisplacement);

    plane->GetTransform()->SetScale(vec3(5, 5, 5)); // The plane has default z 0.5, thus scale 5 means the plane is at z:2.5
    plane->GetTransform()->SetPosition(vec3(0, 0, -6.0f));

    lamp->GetTransform()->SetPosition(vec3(1, 0, -3.0f));
    lamp->GetTransform()->SetScale(vec3(0.1f, 0.1f, 0.1f));

    scene.AddGameObject(camera);
    scene.AddGameObject(plane);
    scene.AddGameObject(lamp);

    scene.preRender = [] {
        plane->GetMeshRender()->GetMaterial()->GetShader()->SetVec3("viewPose", camera->GetTransform()->GetPosition());
        plane->GetMeshRender()->GetMaterial()->GetShader()->SetVec3("lightPos", lamp->GetTransform()->GetPosition());
    };

    scene.MainLoop();
}
