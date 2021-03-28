#include "GO_Quad_TBN.h"
#include "../Mesh/Mesh_Quad_TBN.h"

GO_Quad_TBN::GO_Quad_TBN() : GameObject(), transform(new Transform()), meshRender(new MeshRender())
{
    Debug::Log("Enter Create GO_Quad_TBN");
    name = "GO_Quad_TBN";
    meshRender->SetMesh(new Mesh_Quad_TBN());

    Debug::Log("Before add transform for GO_Quad_TBN");
    AddComponent(transform);
    AddComponent(meshRender);
    Debug::Log("After add meshRender for GO_Quad_TBN");
}

GO_Quad_TBN::GO_Quad_TBN(MeshRender *meshRender) : GameObject(), transform(new Transform())
{
    Debug::Log("Enter Create GO_Quad_TBN");
    name = "GO_Quad_TBN";
    this->meshRender = meshRender;
    this->meshRender->SetMesh(new Mesh_Quad_TBN());

    Debug::Log("Before add transform for GO_Quad_TBN");
    AddComponent(transform);
    AddComponent(meshRender);
    Debug::Log("After add meshRender for GO_Quad_TBN");
}

GO_Quad_TBN::~GO_Quad_TBN()
{
    delete transform;
    delete meshRender;
}

