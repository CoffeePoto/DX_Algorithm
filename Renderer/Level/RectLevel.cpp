#include "RectLevel.h"
#include "Actor/RectActor.h"
#include "Actor/StartActor.h"
#include "Actor/GoalActor.h"
#include "Actor/ObstacleActor.h"
#include "Actor/ArrowActorUp.h"
#include "Actor/ArrowActorDown.h"
#include "Actor/ArrowActorRight.h"
#include "Actor/ArrowActorLeft.h"
#include <vector>

std::vector<std::vector<int>> grid =
//20 * 20 => for���� 0-19, so ��ġ ���� ���� i or j���� -10�� ���Ѵ�.
//��� ���ϴ� ����� 2������ maze, �� �߿��� ������ ������ ã�� �� ������.
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 3, 1 },
	{ 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1 },
	{ 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1 },
	{ 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1 },
	{ 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
	{ 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1 },
	{ 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1 },
	{ 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

RectLevel::RectLevel()
{
	for (int y = 0; y < grid.size(); ++y)
	{
		for (int x = 0; x < grid[0].size(); ++x)
		{
			if (grid[y][x] == 2)
			{
				startActor = new StartActor(XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
				startActor->SetPosition(XMFLOAT3((float)x - 10, (float)10 - y, 10.0f));
				AddActor(startActor);
			}

			if (grid[y][x] == 3)
			{
				goalActor = new GoalActor(XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
				goalActor->SetPosition(XMFLOAT3((float)x - 10, (float)10 - y, 10.0f));
				AddActor(goalActor);
			}

			if (grid[y][x] == 1)
			{
				obstacleActor = new ObstacleActor(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
				obstacleActor->SetPosition(XMFLOAT3((float)x - 10, (float)10 - y, 10.0f));
				AddActor(obstacleActor);
			}
			//�߽�(0, 0)��ġ Ȯ��
			if (x - 10 == 0 && 10 - y == 0)
			{
				Actor* originActor = new RectActor(XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
				originActor->SetPosition(XMFLOAT3((float)x - 10, (float)10 - y, 10.0f));
				AddActor(originActor);
			}
		}
	}

	//astar search �غ�
	Node* startNode = new Node(startActor->GetPosition().x + 10, 10 - startActor->GetPosition().y);
	Node* goalNode = new Node(goalActor->GetPosition().x + 10, 10 - goalActor->GetPosition().y);
	path = aStar.FindPath(startNode, goalNode, grid);

	//for (const Node* node : path)
	//{
	//	arrowActor = new ArrowActorDown(XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f));
	//	arrowActor->SetPosition(XMFLOAT3((float)node->position.x - 10, (float)10 - node->position.y, 10.0f));
	//	AddActor(arrowActor);
	//}

	if (!path.empty())
	{
		for (int i = 1; i < path.size() - 1; ++i)
		{
			if (path[i]->direction == DirectionType::Up)
			{
				arrowActor = new ArrowActorUp(XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (path[i]->direction == DirectionType::Down)
			{
				arrowActor = new ArrowActorDown(XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (path[i]->direction == DirectionType::Left)
			{
				arrowActor = new ArrowActorLeft(XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (path[i]->direction == DirectionType::Right)
			{
				arrowActor = new ArrowActorRight(XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f));
			}
			arrowActor->SetPosition(XMFLOAT3((float)path[i]->position.x - 10, (float)10 - path[i]->position.y, 10.0f));
			AddActor(arrowActor);
		}
	}
}

RectLevel::~RectLevel()
{
}

void RectLevel::Draw()
{
	Level::Draw(); // �̷��� virtual �������̵��� ������ �״�� ������?
	
	if (!path.empty())
	{
		//Todo:��θ� ����� ���ο� Actor�� ���� ���
	}
}
