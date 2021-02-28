#include "GO_InverseCube.h"
#include "../Mesh/Mesh_InverseCube.h"

GO_InverseCube::GO_InverseCube() : GameObject(), transform(new Transform()), meshRender(new MeshRender())
{
    Debug::Log("Enter Create GO_InverseCube");
    name = "GO_InverseCube";
    meshRender->SetMesh(new Mesh_InverseCube());

    Debug::Log("Before add transform for GO_InverseCube");
    AddComponent(transform);
    AddComponent(meshRender);
    Debug::Log("After add meshRender for GO_InverseCube");
}

GO_InverseCube::GO_InverseCube(MeshRender *meshRender) : GameObject(), transform(new Transform())
{
    Debug::Log("Enter Create GO_InverseCube");
    name = "GO_InverseCube";
    this->meshRender = meshRender;
    this->meshRender->SetMesh(new Mesh_InverseCube());

    Debug::Log("Before add transform for GO_InverseCube");
    AddComponent(transform);
    AddComponent(meshRender);
    Debug::Log("After add meshRender for GO_InverseCube");
}

GO_InverseCube::~GO_InverseCube()
{
    delete transform;
    delete meshRender;
}