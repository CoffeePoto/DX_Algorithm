#include "RectLevel.h"
#include "Actor/RectActor.h"

RectLevel::RectLevel()
{
	AddActor(new RectActor(3.0f, 3.0f, 0.0f, 0.0f));
	AddActor(new RectActor(0.0f, 0.0f, -0.3f, -0.3f));
}

RectLevel::~RectLevel()
{
}
