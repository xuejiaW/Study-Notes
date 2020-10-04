#include "GO_Cube.h"
#include "../Mesh/Mesh_Cube.h"

GO_Cube::GO_Cube() : transform(new Transform()), meshRender(new MeshRender()), texture(new Texture("../container.jpg"))
{
    name = "GO_Cube";

    meshRender->SetMesh(new Mesh_Cube());

    AddComponent(transform);
    AddComponent(meshRender);
    AddComponent(texture);
}

GO_Cube::~GO_Cube()
{
    delete transform;
    delete meshRender;
}