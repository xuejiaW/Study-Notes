#include "GO_Plane.h"
#include "../Mesh/Mesh_Plane.h"

GO_Plane::GO_Plane() : GameObject(), transform(new Transform()), meshRender(new MeshRender())
{
    Debug::Log("Enter Create GO_Plane");
    name = "GO_Plane";
    meshRender->SetMesh(new Mesh_Plane());

    Debug::Log("Before add transform for GO_Plane");
    AddComponent(transform);
    AddComponent(meshRender);
    Debug::Log("After add meshRender for GO_Plane");
}

GO_Plane::GO_Plane(MeshRender *meshRender) : GameObject(), transform(new Transform())
{
    Debug::Log("Enter Create GO_Plane");
    name = "GO_Plane";
    this->meshRender = meshRender;
    this->meshRender->SetMesh(new Mesh_Plane());

    Debug::Log("Before add transform for GO_Plane");
    AddComponent(transform);
    AddComponent(meshRender);
    Debug::Log("After add meshRender for GO_Plane");
}

GO_Plane::~GO_Plane()
{
    delete transform;
    delete meshRender;
}

