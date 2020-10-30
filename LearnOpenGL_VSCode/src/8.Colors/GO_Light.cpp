#include "GO_Light.h"
#include "../Framework/Mesh/Mesh_Cube.h"

GO_Light::GO_Light() : transform(new Transform()),
                       meshRender(new MeshRender("../Framework/Shaders/Default.vertex", "./simpleLamp.frag"))
{
    name = "GO_Light";
    meshRender->SetMesh(new Mesh_Cube());
    AddComponent(transform);
    AddComponent(meshRender);
}

GO_Light::~GO_Light()
{
    delete transform;
    delete meshRender;
}