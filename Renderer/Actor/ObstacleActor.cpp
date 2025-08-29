#include "ObstacleActor.h"
#include "Mesh/RectMesh.h"
#include "Shader/Shader.h"

ObstacleActor::ObstacleActor(XMFLOAT4 color)
{
	mesh = new RectMesh(color);
	shader = new Shader(L"HLSLShaders/Default");
}
