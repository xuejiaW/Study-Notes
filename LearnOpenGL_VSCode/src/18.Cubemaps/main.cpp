
#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"
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

Shader *reflectionShader = new Shader("./environmentMapping.vert", "./reflection.frag");
Shader *refractionShader = new Shader("./environmentMapping.vert", "./refraction.frag");

GO_Cube *marbleCubes[2]{
    new GO_Cube(new MeshRender(reflectionShader)),
    new GO_Cube(new MeshRender(refractionShader))};

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

    // Adding reflection cube and refraction cube
    vec3 marbleCubePos[2] = {vec3{-0.3, 0, 0.5}, vec3{0.3, 0, -3}};

    marbleCubes[0]->GetMeshRender()->SetPreRenderHandle([]() {
        vec3 cameraPos = camera->GetTransform()->GetPosition();
        reflectionShader->SetVec3("cameraPos", cameraPos);

        //// Try to make the cube moving with the camera ( keep the relative position the same)
        //// and it turns out that it will not cause any reflection effect changing, which do not meet the real situation
        //// Imaging that someone takes a mirror and moves with it, the image in the mirror definitely will be changed

        // cameraPos[2] -= 2.5;
        // marbleCubes[0]->GetTransform()->SetPosition(cameraPos);
    });

    marbleCubes[1]->GetMeshRender()->SetPreRenderHandle([]() {
        refractionShader->SetVec3("cameraPos", camera->GetTransform()->GetPosition());
    });

    for (int i = 0; i != 2; ++i)
    {
        marbleCubes[i]->GetTransform()->SetPosition(marbleCubePos[i]);
        marbleCubes[i]->GetMeshRender()->GetMaterial()->AddTexture("ourTexture", cubemap);
        marbleCubes[i]->GetTransform()->SetScale(vec3(1, 1, 1));
        scene.AddGameObject(marbleCubes[i]);
    }

    // Version: Draw skybox in the end
    Skybox *skybox = new Skybox(cubemap);
    skybox->preRender = []() { glDepthFunc(GL_LEQUAL); };
    skybox->postRender = []() { glDepthFunc(GL_LESS); };
    scene.AddGameObject(skybox);

    scene.MainLoop();
}
