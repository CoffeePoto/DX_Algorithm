#include "RectActor.h"
#include "Mesh/RectMesh.h"

RectActor::RectActor()
{
	mesh = new RectMesh();
	shader = new Shader(L"HLSLShaders/Default");
}	
