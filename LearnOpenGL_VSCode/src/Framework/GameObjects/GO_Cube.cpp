#include "GO_Cube.h"
#include "../Mesh/Mesh_Cube.h"

GO_Cube::GO_Cube() : GameObject(), transform(new Transform()), meshRender(new MeshRender())
{
    name = "GO_Cube";
    meshRender->SetMesh(new Mesh_Cube());

    AddComponent(transform);
    AddComponent(meshRender);
}

GO_Cube::GO_Cube(MeshRender *meshRender) : GameObject(), transform(new Transform())
{
    Debug::Log("Enter Create GO_Cube");
    name = "GO_Cube";
    this->meshRender = meshRender;
    this->meshRender->SetMesh(new Mesh_Cube());

    Debug::Log("Before add transform for GO_Cube");
    AddComponent(transform);
    AddComponent(meshRender);
    Debug::Log("After add meshRender for GO_Cube");
}

GO_Cube::~GO_Cube()
{
    delete transform;
    delete meshRender;
}