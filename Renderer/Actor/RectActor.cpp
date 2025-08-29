#include "RectActor.h"
#include "Mesh/RectMesh.h"

RectActor::RectActor(XMFLOAT4 color)
{
	mesh = new RectMesh(color);
	shader = new Shader(L"HLSLShaders/Default");
}	
