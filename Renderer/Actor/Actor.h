#pragma once

#include "Utils.h"
#include "Math/Transform.h"

class Mesh;
class Shader;
class Level;
class Actor
{
public:
	Actor();
	virtual ~Actor();

	//연산자 오버로딩 for Astar
	bool operator==(const Actor& other) const
	{
		return transform.GetPosition().x == other.GetPosition().x
			&& transform.GetPosition().y == other.GetPosition().y;
	}

	Transform operator-(const Actor& other) const
	{
		float newX = transform.GetPosition().x - other.GetPosition().x;
		float newY = transform.GetPosition().y - other.GetPosition().y;
		Transform newPosition;
		newPosition.SetPosition(XMFLOAT3(newX, newY, transform.GetPosition().z));
		return newPosition;
	}

	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void Destroy();

	Level* GetOwner() const { return owner; }
	void SetOwner(Level* newOwner);
	bool IsDestroyed() const { return isExpired; }

	void SetPosition(const XMFLOAT3& newPosition);
	XMFLOAT3 GetPosition() const;

	Transform GetTransform() const;

protected:
	bool isExpired = false;
	Mesh* mesh = nullptr;
	Shader* shader = nullptr;
	Level* owner = nullptr;

	Transform transform;
	//for Astar
public:
	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;
	Actor* parent = nullptr;
};