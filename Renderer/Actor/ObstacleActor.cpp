#include "ObstacleActor.h"
#include "Mesh/ObstacleMesh.h"

ObstacleActor::ObstacleActor(float bottomx, float bottomy)
{
	mesh = new ObstacleMesh(bottomx, bottomy);
	shader = new Shader(L"HLSLShaders/Default");
}
