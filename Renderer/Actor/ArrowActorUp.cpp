#include "ArrowActorUp.h"
#include "Mesh/ArrowMeshUp.h"

ArrowActorUp::ArrowActorUp(XMFLOAT4 color)
{
	mesh = new ArrowMeshUp(color);
	shader = new Shader(L"HLSLShaders/Default");
}
