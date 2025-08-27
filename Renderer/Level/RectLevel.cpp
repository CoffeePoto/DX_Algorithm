#include "RectLevel.h"
#include "Actor/RectActor.h"

RectLevel::RectLevel()
{
	AddActor(new RectActor());
}

RectLevel::~RectLevel()
{
}
