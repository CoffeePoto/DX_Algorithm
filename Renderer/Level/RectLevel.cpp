#include "RectLevel.h"
#include "Actor/RectActor.h"
#include "Actor/StartActor.h"
#include "Actor/GoalActor.h"
#include "Actor/ObstacleActor.h"
#include <vector>

std::vector<std::vector<int>> grid =
//20 * 20 => for문이 0-19, so 위치 잡을 때는 i or j에서 -10을 더한다.
//골로 향하는 방식이 2가지인 maze, 그 중에서 최적의 방향을 찾을 수 있을지.
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
	//Actor* startActor = new StartActor(XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	//startActor->SetPosition(XMFLOAT3(-9.0f, -9.0f, 10.0f));
	//AddActor(startActor);
	//Actor* goalActor = new GoalActor(XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
	//goalActor->SetPosition(XMFLOAT3(8.0f, 8.0f, 10.0f));
	//AddActor(goalActor);
	////테두리 그리기
	//for (int i = -10; i < 10; ++i)
	//{
	//	Actor* UpWallActor = new ObstacleActor(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//	UpWallActor->SetPosition(XMFLOAT3(float(i), 9.0f, 10.0f));
	//	AddActor(UpWallActor);
	//	Actor* DownWallActor = new ObstacleActor(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//	DownWallActor->SetPosition(XMFLOAT3(float(i), -10.0f, 10.0f));
	//	AddActor(DownWallActor);
	//	Actor* LeftWallActor = new ObstacleActor(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//	LeftWallActor->SetPosition(XMFLOAT3(-10.0f, float(i), 10.0f));
	//	AddActor(LeftWallActor);
	//	Actor* RightWallActor = new ObstacleActor(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	//	RightWallActor->SetPosition(XMFLOAT3(9.0f, float(i), 10.0f));
	//	AddActor(RightWallActor);
	//}
	for (int y = 0; y < grid.size(); ++y)
	{
		for (int x = 0; x < grid[0].size(); ++x)
		{
			if (grid[y][x] == 2)
			{
				Actor* startActor = new StartActor(XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
				startActor->SetPosition(XMFLOAT3(x - 10, 10 - y, 10.0f));
				AddActor(startActor);
			}

			if (grid[y][x] == 3)
			{
				Actor* goalActor = new GoalActor(XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
				goalActor->SetPosition(XMFLOAT3(x - 10, 10 - y, 10.0f));
				AddActor(goalActor);
			}

			if (grid[y][x] == 1)
			{
				Actor* obstacleActor = new ObstacleActor(XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
				obstacleActor->SetPosition(XMFLOAT3(x - 10, 10 - y, 10.0f));
				AddActor(obstacleActor);
			}
		}
	}
}

RectLevel::~RectLevel()
{
}
