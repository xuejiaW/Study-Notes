
#include "GO_Point.h"
#include "../Mesh/Mesh_Point.h"

GO_Point::GO_Point() : GameObject(), transform(new Transform()), meshRender(new MeshRender())
{
    Debug::Log("Enter Create GO_Point");
    name = "GO_Point";
    meshRender->SetMesh(new Mesh_Point());

    Debug::Log("Before add transform for GO_Point");
    // AddComponent(transform);
    AddComponent(meshRender);
    Debug::Log("After add meshRender for GO_Point");
}

GO_Point::GO_Point(MeshRender *meshRender) : GameObject(), transform(new Transform())
{
    Debug::Log("Enter Create GO_Point");
    name = "GO_Point";
    this->meshRender = meshRender;
    this->meshRender->SetMesh(new Mesh_Point());

    Debug::Log("Before add transform for GO_Point");
    // AddComponent(transform);
    AddComponent(meshRender);
    Debug::Log("After add meshRender for GO_Point");
}

GO_Point::~GO_Point()
{
    delete transform;
    delete meshRender;
}