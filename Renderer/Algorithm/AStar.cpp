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

	//�����¿�, �밢�� ���� �� ���
	static const std::vector<Direction> directions =
	{
		// �ϻ���� �̵�.
		{ 0, 1, 1.0f }, { 0, -1, 1.0f }, { 1, 0, 1.0f }, { -1, 0, 1.0f },

		// �밢�� �̵�.
		{ 1, 1, 1.414f }, { 1, -1, 1.414f }, { -1, 1, 1.414f }, { -1, -1, 1.414f }
	};

	while (!openList.empty())
	{
		// ���� ���� ����Ʈ���� fCost�� ���� ���� ��� �˻�.
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

		//���� ��Ͽ� �߰�.
		for (int i = 0; i < (int)openList.size(); ++i)
		{
			if (*openList[i] == *currentNode)
			{
				//iterator�� Ȱ���� ���� �迭���� ��� ����
				openList.erase(openList.begin() + i);
				break;
			}
		}

		//���� ��带 ���� ��Ͽ� �߰�
		//�̹� ������ �߰�x, ������ �߰�
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
		// �̿� ��� �湮(Ž��). (��/��/��/�� ���ʷ� �湮).
		for (const Direction& direction : directions)
		{
			// ������ �̵��� ��ġ ����.
			int newX = currentNode->position.x + direction.x;
			int newY = currentNode->position.y + direction.y;

			// �׸��� ���̸� ����.
			if (!IsInRange(newX, newY, grid))
			{
				continue;
			}

			// �̵��� ��ġ�� ��ֹ��� ��쿡�� ����.
			if (grid[newY][newX] == 1)
			{
				continue;
			}

			//�̹� �湮������ ����, �̹� �湮�ߴ��� Ȯ���ϴ� �Լ� ȣ��
			float gCost = currentNode->gCost + direction.cost;
			if (HasVisited(newX, newY, gCost)) continue;

			Node* neighborNode = new Node(newX, newY, currentNode);
			neighborNode->gCost = currentNode->gCost + direction.cost;
			//heuristic ��� ��� �Լ� ȣ��
			neighborNode->hCost = CalculateHeuristic(neighborNode, goalNode);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

			//�̿� ��尡 ���� ����Ʈ�� �ִ��� Ȯ��
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
				grid[newY][newX] = 5;
				openList.emplace_back(neighborNode);
			}
			else
			{
				SafeDelete(neighborNode);
			}

			//������
			DisplayGrid(grid);
			int delay = (int)(0.1f * 1000);
			Sleep(delay);
		}
	}

	return std::vector<Node*>();
}

void AStar::DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path)
{
	static COORD position = { 0, 0 };
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, position);

	int white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	int green = FOREGROUND_GREEN;

	// ������ ���� �����ߴ� ������ �ʱ�ȭ.
	for (int y = 0; y < grid.size(); ++y)
	{
		for (int x = 0; x < grid[0].size(); ++x)
		{
			int& value = grid[y][x];
			if (value == 2 || value == 3 || value == 5)
			{
				value = 0;
			}
		}
	}

	// ��θ� ������ �� ���.
	for (int y = 0; y < grid.size(); ++y)
	{
		for (int x = 0; x < grid[0].size(); ++x)
		{
			// ��ֹ�.
			if (grid[y][x] == 1)
			{
				SetConsoleTextAttribute(handle, white);
				std::cout << "1 ";
			}


			// �� ����.
			else if (grid[y][x] == 0)
			{
				SetConsoleTextAttribute(handle, white);
				std::cout << "0 ";
			}
		}

		std::cout << "\n";
	}

	// ��� ���.
	for (const Node* node : path)
	{
		// ��δ� '2'�� ǥ��.
		COORD position{ static_cast<short>(node->position.x * 2), static_cast<short>(node->position.y) };
		SetConsoleCursorPosition(handle, position);
		SetConsoleTextAttribute(handle, green);

		std::cout << "* ";
		int delay = static_cast<int>(0.05f * 1000);
		Sleep(delay);
	}
}

std::vector<Node*> AStar::ConstructPath(Node* goalNode)
{
	//��� ��ȯ�ϴ� �Լ� ���� ����
	std::vector<Node*> path;
	Node* currentNode = goalNode;
	while (currentNode != nullptr)
	{
		path.emplace_back(currentNode);
		currentNode = currentNode->parent;
	}

	//���ݱ����� ��δ� ����->��ǥ
	//������� �Ѵ�.
	std::reverse(path.begin(), path.end());

	return path;
}

bool AStar::IsDestination(const Node* node)
{
	return *node == *goalNode;
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
{
	//x, y ���� ����� false
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
			//��ġ�� ������ ����� �� ũ�� �湮�� ���� ����
			if (node->gCost < gCost) return true;
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
			if (node->gCost > gCost) return true;
			else if (node->gCost > gCost)
			{
				closedList.erase(closedList.begin() + i);
				SafeDelete(node);
			}
		}
	}
	//��Ͽ� ���ٸ� �Ǵ��ϸ� �湮���� ���� ������ ����
	return false;
}

float AStar::CalculateHeuristic(Node* currentNode, Node* goalNode)
{
	Position diff = *currentNode - *goalNode;
	return (float)std::sqrt(diff.x * diff.x + diff.y * diff.y);
}

void AStar::DisplayGrid(std::vector<std::vector<int>>& grid)
{
	static COORD position = { 0, 0 };
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, position);

	int white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	int green = FOREGROUND_GREEN;

	for (int y = 0; y < grid.size(); ++y)
	{
		for (int x = 0; x < grid[0].size(); ++x)
		{
			// ���� ��ġ.
			if (grid[y][x] == 2)
			{
				SetConsoleTextAttribute(handle, FOREGROUND_RED);
				std::cout << "S ";
			}

			// ��ǥ ��ġ.
			if (grid[y][x] == 3)
			{
				SetConsoleTextAttribute(handle, FOREGROUND_RED);
				std::cout << "G ";
			}

			// ��ֹ�.
			if (grid[y][x] == 1)
			{
				SetConsoleTextAttribute(handle, white);
				std::cout << "1 ";
			}

			// ���.
			else if (grid[y][x] == 5)
			{
				SetConsoleTextAttribute(handle, green);
				std::cout << "+ ";
			}

			// �� ����.
			else if (grid[y][x] == 0)
			{
				SetConsoleTextAttribute(handle, white);
				std::cout << "0 ";
			}
		}

		std::cout << "\n";
	}
}


