#include "ArrowActorDown.h"
#include "Mesh/ArrowMeshDown.h"

ArrowActorDown::ArrowActorDown(XMFLOAT4 color)
{
	mesh = new ArrowMeshDown(color);
	shader = new Shader(L"HLSLShaders/Default");
}
