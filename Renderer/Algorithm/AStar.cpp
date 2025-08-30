#include "AStar.h"
#include <Windows.h>

AStar::AStar()
{
}

AStar::~AStar()
{
}

std::vector<Node*> AStar::FindPath(Node* startNode, Node* goalNode, std::vector<std::vector<int>>& grid)
{
	this->startNode = startNode;
	this->goalNode = goalNode;

	openList.emplace_back(startNode);

	//상하좌우, 대각선 방향 및 비용
	static const std::vector<Direction> directions =
	{
		// 우좌하상 이동.
		{ 1, 0, 1.0f, DirectionType::Right }, { -1, 0, 1.0f, DirectionType::Left }, 
		{ 0, 1, 1.0f, DirectionType::Down }, { 0, -1, 1.0f, DirectionType::Up }
	};

	while (!openList.empty())
	{
		OutputDebugStringA("Test Output from openList!\n");
		// 현재 열린 리스트에서 fCost가 가장 낮은 노드 검색.
		Node* lowestNode = openList[0];
		for (Node* node : openList)
		{
			if (node->fCost < lowestNode->fCost)
			{
				lowestNode = node;
			}
		}
		Node* currentNode = lowestNode;

		if (IsDestination(currentNode))
		{
			return ConstructPath(currentNode);
		}

		//닫힌 목록에 추가.
		for (int i = 0; i < (int)openList.size(); ++i)
		{
			if (*openList[i] == *currentNode)
			{
				//iterator를 활용해 동적 배열에서 노드 제거
				openList.erase(openList.begin() + i);
				break;
			}
		}

		//현재 노드를 닫힌 목록에 추가
		//이미 있으면 추가x, 없으면 추가
		bool isNodeInList = false;
		for (Node* node : closedList)
		{
			if (*node == *currentNode)
			{
				isNodeInList = true;
				break;
			}
		}

		if (isNodeInList) continue;
		closedList.emplace_back(currentNode);
		// 이웃 노드 방문(탐색). (하/상/우/좌 차례로 방문).
		for (const Direction& direction : directions)
		{
			// 다음에 이동할 위치 설정.
			int newX = currentNode->position.x + direction.x;
			int newY = currentNode->position.y + direction.y;

			// 그리드 밖이면 무시.
			if (!IsInRange(newX, newY, grid))
			{
				continue;
			}

			// 이동할 위치가 장애물인 경우에는 무시.
			if (grid[newY][newX] == 1)
			{
				continue;
			}

			//이미 방문했으면 무시, 이미 방문했는지 확인하는 함수 호출
			float gCost = currentNode->gCost + direction.cost;
			if (HasVisited(newX, newY, gCost)) continue;

			Node* neighborNode = new Node(newX, newY, currentNode);
			neighborNode->direction = direction.type;
			neighborNode->gCost = currentNode->gCost + direction.cost;
			//heuristic 비용 계산 함수 호출
			neighborNode->hCost = CalculateHeuristic(neighborNode, goalNode);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

			//이웃 노드가 열린 리스트에 있는지 확인
			Node* openListNode = nullptr;
			for (Node* node : openList)
			{
				if (*node == *neighborNode)
				{
					openListNode = node;
					break;
				}
			}

			if (openListNode == nullptr
				|| openListNode->gCost > neighborNode->gCost
				|| openListNode->fCost > neighborNode->fCost)
			{
				  //grid[newY][newX] = 5;
				openList.emplace_back(neighborNode);
				//for debug
				char debug[128];
				sprintf_s(debug, "Add to openList: (%d, %d)\n", newX, newY);
				OutputDebugStringA(debug);
			}
			else
			{
				SafeDelete(neighborNode);
			}
		}
	}

	return std::vector<Node*>();
}

std::vector<Node*> AStar::ConstructPath(Node* goalNode)
{
	//경로 반환하는 함수 로직 구현
	std::vector<Node*> path;
	Node* currentNode = goalNode;
	while (currentNode != nullptr)
	{
		path.emplace_back(currentNode);
		currentNode = currentNode->parent;
	}

	while (currentNode != nullptr)
	{
		// 디버그 문자열 출력
		char buffer[128];
		sprintf_s(buffer, "Path node: (%d, %d)\n", currentNode->position.x, currentNode->position.y);
		OutputDebugStringA(buffer); // ANSI 문자열 출력

		path.emplace_back(currentNode);
		currentNode = currentNode->parent;
	}

	//지금까지의 경로는 시작->목표
	//뒤집어야 한다.
	std::reverse(path.begin(), path.end());

	return path;
}

bool AStar::IsDestination(const Node* node)
{
	return *node == *goalNode;
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
{
	//x, y 범위 벗어나면 false
	if (x < 0 || y < 0 || x >= (int)grid[0].size() || y >= (int)grid.size())
	{
		return false;
	}

	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
	for (int i = 0; i < (int)openList.size(); ++i)
	{
		Node* node = openList[i];
		if (node->position.x == x && node->position.y == y)
		{
			//위치가 같은데 비용이 더 크면 방문할 이유 없음
			if (node->gCost <= gCost) return true;
			else if (node->gCost > gCost)
			{
				openList.erase(openList.begin() + i);
				SafeDelete(node);
			}
		}
	}

	for (int i = 0; i < (int)closedList.size(); ++i)
	{
		Node* node = closedList[i];
		if (node->position.x == x && node->position.y == y)
		{
			if (node->gCost <= gCost) return true;
			else if (node->gCost > gCost)
			{
				closedList.erase(closedList.begin() + i);
				SafeDelete(node);
			}
		}
	}
	//목록에 없다면 판단하면 방문하지 않은 것으로 간주
	return false;
}

float AStar::CalculateHeuristic(Node* currentNode, Node* goalNode)
{
	Position diff = *currentNode - *goalNode;
	return (float)std::sqrt(diff.x * diff.x + diff.y * diff.y);
}


