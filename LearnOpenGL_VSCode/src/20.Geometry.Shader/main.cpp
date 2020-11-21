#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Point.h"

Scene scene(800, 600, "GeometryShader");
Shader *houseShader = new Shader("./house.vert", "./house.frag", "./house.geo");
GO_Point *housePoint = new GO_Point(new MeshRender(houseShader));

int main()
{
    housePoint->GetMeshRender()->SetDrawingMode(GL_POINTS);
    scene.AddGameObject(housePoint);
    scene.MainLoop();
}