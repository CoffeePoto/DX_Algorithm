#pragma once
#pragma once

#include <vector>
#include "Algorithm/AStar.h"

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

protected:
	AStar aStar;
	std::vector<Node*> path;

private:
	std::vector<Actor*> actors;
	std::vector<Actor*> addRequestedActors;
	std::vector<Actor*> destroyRequestedActors;
};