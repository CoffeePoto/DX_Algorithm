#include "GoalActor.h"
#include "Mesh/RectMesh.h"
#include "Shader/Shader.h"

GoalActor::GoalActor(XMFLOAT4 color)
{
	mesh = new RectMesh(color);
	shader = new Shader(L"HLSLShaders/Default");
}
