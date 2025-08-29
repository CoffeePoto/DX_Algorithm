#pragma once

#include "Node.h"
#include <vector>

class Node;
class AStar
{
private:

	// 방향 처리를 위한 구조체.
	struct Direction
	{
		// 위치.
		int x;
		int y;

		// 이동 비용
		float cost;
	};

public:
	AStar();
	~AStar();

	// 경로 탐색 함수.
	std::vector<Node*> FindPath(
		Node* startNode,
		Node* goalNode,
		std::vector<std::vector<int>>& grid
	);
	
	// 그리드 출력 함수.
	void DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path);

private:
	//탐색을 마친 후 경로를 조립하는 함수
	std::vector<Node*> ConstructPath(Node* goalNode);

	//목표 노드 체크
	bool IsDestination(const Node* node);

	//그리도 안에 있는지 확인
	bool IsInRange(int x, int y, const std::vector<std::vector<int>>& grid);

	bool HasVisited(int x, int y, float gCost);

	//현재 지점에서 목표 지점까지의 추정 비용 계산 함수
	float CalculateHeuristic(Node* currentNode, Node* goalNode);

	void DisplayGrid(std::vector<std::vector<int>>& grid);

private:
	std::vector<Node*> openList;
	std::vector<Node*> closedList;
	Node* startNode = nullptr;
	Node* goalNode = nullptr;
};