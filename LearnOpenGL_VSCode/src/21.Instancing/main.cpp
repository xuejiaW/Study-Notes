#include "../Framework/Scene.h"
#include "../Framework/GameObjects/GO_Plane.h"

Scene scene(800, 600, "Instancing");

glm::vec2 translations[100];
void BindInstanceVBO();

int main()
{
    int index = 0;
    float offset = 0.1f;
    for (int y = -15; y < 15; y += 3)
    {
        for (int x = -15; x < 15; x += 3)
        {
            glm::vec2 translation;
            translation.x = (float)x / 10.0f + offset;
            translation.y = (float)y / 10.0f + offset;
            translations[index++] = translation;
        }
    }

    // // instancing Uniform Data
    // Shader *instanceUnifromShader = new Shader("./instancingUniform.vert", "../Framework/Shaders/Default.fs");
    // GO_Plane *go_plane = new GO_Plane(new MeshRender(instanceUnifromShader));
    // instanceUnifromShader->Use();
    // for (int i = 0; i != 100; ++i)
    //     instanceUnifromShader->SetVec2("offsets[" + std::to_string(i) + "]", translations[i]);

    //instancing layout Data
    Shader *instanceLayoutShader = new Shader("./instancingLayout.vert", "../Framework/Shaders/Default.fs");
    MeshRender *instanceLayoutMeshRender = new MeshRender(instanceLayoutShader);
    instanceLayoutMeshRender->SetLoadingBufferHandle(BindInstanceVBO);
    GO_Plane *go_plane = new GO_Plane(instanceLayoutMeshRender);

    go_plane->GetMeshRender()->SetInstancingCount(100);
    go_plane->GetTransform()->SetScale(vec3(0.1, 0.1, 0.1));

    scene.AddGameObject(go_plane);
    scene.MainLoop();
}

void BindInstanceVBO()
{
    unsigned int instanceVBO;
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glVertexAttribDivisor(3, 1);
}

