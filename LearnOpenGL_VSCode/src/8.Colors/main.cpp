#include "./GO_Light.h"
#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Camera.h"
#include "../Framework/GameObjects/GO_Cube.h"
#include "../Framework/Mesh/Mesh_Cube.h"

int main()
{
    Scene scene(800, 600, "Color");

    GO_Camera *camera = new GO_Camera();
    scene.AddGameObject(camera);

    // MeshRender for lamp
    MeshRender *lightMeshRender = new MeshRender("../Framework/Shaders/Default.vertex", "./lamp.frag");
    Shader &lightShader = lightMeshRender->GetShader();
    lightShader.Use();
    glUniform3fv(glGetUniformLocation(lightShader.Program, "lightColor"), 1, value_ptr(vec3(1, 1, 1)));

    GO_Cube *lamp = new GO_Cube(lightMeshRender);
    lamp->GetTransform()->SetPosition(vec3(1.2f, 1.0f, -2.0f));
    scene.AddGameObject(lamp);

    // MeshRender for colored Cube
    MeshRender *coloredCubeMeshRender = new MeshRender("../Framework/Shaders/Default.vertex", "./colorObject.frag");
    Shader &cubeShader = coloredCubeMeshRender->GetShader();
    cubeShader.Use();
    glUniform3fv(glGetUniformLocation(cubeShader.Program, "lightColor"), 1, value_ptr(vec3(1, 1, 1)));
    glUniform3fv(glGetUniformLocation(cubeShader.Program, "objectColor"), 1, value_ptr(vec3(1, 0, 0)));

    GO_Cube *coloredCube = new GO_Cube(coloredCubeMeshRender);
    scene.AddGameObject(coloredCube);

    scene.MainLoop();
}