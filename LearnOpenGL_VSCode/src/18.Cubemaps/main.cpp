
#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/GameObjects/GO_Plane.h"
#include "../Framework/Components/Cubemap.h"
#include "../Framework/Components/Skybox.h"

#include <vector>
#include <string>

using std::string;
using std::vector;

vector<std::string> faces{
    "../skybox/right.jpg",
    "../skybox/left.jpg",
    "../skybox/top.jpg",
    "../skybox/bottom.jpg",
    "../skybox/front.jpg",
    "../skybox/back.jpg"};

Scene scene(800, 600, "Cubemaps");
GO_Camera *camera = nullptr;

int main()
{
    camera = new GO_Camera();
    scene.AddGameObject(camera);

    Cubemap *cubemap = new Cubemap(faces);

    // // Version: Firstly draw Cubemap
    // Skybox *skybox = new Skybox(cubemap);
    // skybox->preRender = []() {
    //     glDepthMask(GL_FALSE); // Turn off Depth Buffer
    // };

    // skybox->postRender = []() {
    //     glDepthMask(GL_TRUE); // Turn on Depth Buffer
    // };
    // scene.AddGameObject(skybox);

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

    // Version: Draw skybox in the end
    Skybox *skybox = new Skybox(cubemap);
    skybox->preRender = []() { glDepthFunc(GL_LEQUAL); };
    skybox->postRender = []() { glDepthFunc(GL_LESS); };
    scene.AddGameObject(skybox);

    scene.MainLoop();
}
