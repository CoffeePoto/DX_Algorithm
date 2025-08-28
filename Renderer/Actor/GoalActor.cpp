#include "GoalActor.h"
#include "Mesh/GoalMesh.h"

GoalActor::GoalActor(float topx, float topy, float bottomx, float bottomy)
{
	mesh = new GoalMesh(topx, topy, bottomx, bottomy);
	shader = new Shader(L"HLSLShaders/Default");
}
