#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"

int main()
{
    Scene scene(800, 600, "Color");

    GO_Camera *camera = new GO_Camera();
    scene.AddGameObject(camera);

    GO_Cube *cube = new GO_Cube();
    scene.AddGameObject(cube);

    scene.MainLoop();
}