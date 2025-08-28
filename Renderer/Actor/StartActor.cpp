#include "StartActor.h"
#include "Mesh/StartMesh.h"

StartActor::StartActor(float topx, float topy, float bottomx, float bottomy)
{
	mesh = new StartMesh(topx, topy, bottomx, bottomy);
	shader = new Shader(L"HLSLShaders/Default");
}
