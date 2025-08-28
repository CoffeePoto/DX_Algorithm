#include "RectLevel.h"
#include "Actor/RectActor.h"
#include "Actor/StartActor.h"
#include "Actor/GoalActor.h"
#include "Actor/ObstacleActor.h"

RectLevel::RectLevel()
{
	//AddActor(new RectActor(3.0f, 3.0f, 0.0f, 0.0f));
	AddActor(new GoalActor(4.0f, 4.0f, 2.0f, 2.0f));
	AddActor(new StartActor(-5.0f, -3.0f, -5.3f, -3.3f));
	for (int i = 0; i < 3; ++i)
	{
		AddActor(new ObstacleActor(0.0f, 2.0f + i));
	}
}

RectLevel::~RectLevel()
{
}
