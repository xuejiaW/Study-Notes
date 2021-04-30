#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/Data/Model.h"

const int screen_width = 1024, screen_height = 1024;

Scene scene(screen_width, screen_height, "Model Loading");
GO_Camera *camera = new GO_Camera();

Shader *modelShader = new Shader("../Framework/Shaders/ModelDefault.vs", "../Framework/Shaders/ModelDefault.fs");
Model *model = new Model("../Model/Bag/backpack.obj", modelShader);

int main()
{
    scene.AddGameObject(camera);
    scene.AddGameObject(model);

    scene.MainLoop();
}
