#pragma once
#pragma once

#include <vector>

class Actor;
class Level
{
public:
	Level() = default;
	virtual ~Level();

	virtual void Update(float deltaTime);
	virtual void Draw();

	void AddActor(Actor* newActor);
	void DestroyActor(Actor* deleteActor);

	void ProcessAddAndDeleteActor();

private:
	std::vector<Actor*> actors;
	std::vector<Actor*> addRequestedActors;
	std::vector<Actor*> destroyRequestedActors;
};