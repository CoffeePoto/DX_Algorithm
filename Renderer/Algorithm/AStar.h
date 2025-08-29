#pragma once

#include "Node.h"
#include <vector>

class Node;
class AStar
{
private:

	// ���� ó���� ���� ����ü.
	struct Direction
	{
		// ��ġ.
		int x;
		int y;

		// �̵� ���
		float cost;
	};

public:
	AStar();
	~AStar();

	// ��� Ž�� �Լ�.
	std::vector<Node*> FindPath(
		Node* startNode,
		Node* goalNode,
		std::vector<std::vector<int>>& grid
	);
	
	// �׸��� ��� �Լ�.
	void DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path);

private:
	//Ž���� ��ģ �� ��θ� �����ϴ� �Լ�
	std::vector<Node*> ConstructPath(Node* goalNode);

	//��ǥ ��� üũ
	bool IsDestination(const Node* node);

	//�׸��� �ȿ� �ִ��� Ȯ��
	bool IsInRange(int x, int y, const std::vector<std::vector<int>>& grid);

	bool HasVisited(int x, int y, float gCost);

	//���� �������� ��ǥ ���������� ���� ��� ��� �Լ�
	float CalculateHeuristic(Node* currentNode, Node* goalNode);

	void DisplayGrid(std::vector<std::vector<int>>& grid);

private:
	std::vector<Node*> openList;
	std::vector<Node*> closedList;
	Node* startNode = nullptr;
	Node* goalNode = nullptr;
};