#pragma once
#include "Level.h"

class RectLevel : public Level
{
public:
	RectLevel();
	~RectLevel();

	void Draw();
private:
	Actor* startActor;
	Actor* goalActor;
	Actor* obstacleActor;
	Actor* arrowActor;
};