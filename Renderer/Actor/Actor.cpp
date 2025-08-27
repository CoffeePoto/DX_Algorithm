#include "Actor.h"
#include "Mesh/Mesh.h"
#include "Shader/Shader.h"

Actor::Actor()
{
}

Actor::~Actor()
{
	SafeDelete(shader);
	SafeDelete(mesh);
}

void Actor::Update(float deltaTime)
{
}

void Actor::Draw()
{
	if (shader && mesh)
	{
		shader->Bind();
		mesh->Draw();
	}
}

void Actor::SetOwner(Level* newOwner)
{
	owner = newOwner;
}

void Actor::Destroy()
{
	isExpired = true;
}