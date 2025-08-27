#include "Level.h"
#include "Actor/Actor.h"
#include "Utils.h"

Level::~Level()
{
	for (Actor* actor : actors)
	{
		SafeDelete(actor);
	}
	actors.clear();
}

void Level::Update(float deltaTime)
{
	for (Actor* actor : actors)
	{
		if (actor->IsDestroyed())
		{
			continue;
		}

		actor->Update(deltaTime);
	}
}

void Level::Draw()
{
	for (Actor* actor : actors)
	{
		if (actor->IsDestroyed())
		{
			continue;
		}

		actor->Draw();
	}
}

void Level::AddActor(Actor* newActor)
{
	addRequestedActors.emplace_back(newActor);
}

void Level::DestroyActor(Actor* deleteActor)
{
	destroyRequestedActors.emplace_back(deleteActor);
}

void Level::ProcessAddAndDeleteActor()
{
	for (auto iterator = actors.begin(); iterator != actors.end(); )
	{
		if ((*iterator)->IsDestroyed())
		{
			iterator = actors.erase(iterator);
			continue;
		}

		++iterator;
	}

	for (Actor* actor : destroyRequestedActors)
	{
		SafeDelete(actor);
	}
	destroyRequestedActors.clear();

	for (Actor* actor : addRequestedActors)
	{
		actors.emplace_back(actor);
		actor->SetOwner(this);
	}
	addRequestedActors.clear();
}