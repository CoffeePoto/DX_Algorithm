#include "RectActor.h"
#include "Mesh/RectMesh.h"

RectActor::RectActor(float topx, float topy, float bottomx, float bottomy)
{
	mesh = new RectMesh(topx, topy, bottomx, bottomy);
	shader = new Shader(L"HLSLShaders/Default");
}	
