#pragma once
#pragma once

class Mesh;
class Shader;
class Level;
class Actor
{
public:
	Actor();
	virtual ~Actor();

	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void Destroy();

	Level* GetOwner() const { return owner; }
	void SetOwner(Level* newOwner);
	bool IsDestroyed() const { return isExpired; }

protected:
	bool isExpired = false;
	Mesh* mesh = nullptr;
	Shader* shader = nullptr;
	Level* owner = nullptr;
};