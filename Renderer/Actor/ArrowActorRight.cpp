#include "ArrowActorRight.h"
#include "Mesh/ArrowMeshRight.h"

ArrowActorRight::ArrowActorRight(XMFLOAT4 color)
{
	mesh = new ArrowMeshRight(color);
	shader = new Shader(L"HLSLShaders/Default");
}
