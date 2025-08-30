#include "ArrowActorLeft.h"
#include "Mesh/ArrowMeshLeft.h"

ArrowActorLeft::ArrowActorLeft(XMFLOAT4 color)
{
	mesh = new ArrowMeshLeft(color);
	shader = new Shader(L"HLSLShaders/Default");
}
