#include "StartActor.h"
#include "Mesh/RectMesh.h"

StartActor::StartActor(XMFLOAT4 color)
{
	mesh = new RectMesh(color);
	shader = new Shader(L"HLSLShaders/Default");
}
