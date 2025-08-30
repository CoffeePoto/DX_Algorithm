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
	transform.Bind();
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

void Actor::SetPosition(const XMFLOAT3& newPosition)
{
	transform.SetPosition(newPosition);
}

XMFLOAT3 Actor::GetPosition() const
{
	return transform.GetPosition();
}

Transform Actor::GetTransform() const
{
	return transform;
}
