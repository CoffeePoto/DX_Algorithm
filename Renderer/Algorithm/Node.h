#pragma once

#include <iostream>

struct Position
{
	Position(int x = 0, int y = 0)
		: x(x), y(y)
	{

	}

	bool operator==(const Position& other)
	{
		return x == other.x && y == other.y;
	}

	int x = 0;
	int y = 0;
};

enum class DirectionType
{
	Up,
	Down,
	Left,
	Right
};
// 방향 처리를 위한 구조체.
struct Direction
{
	// 위치.
	int x;
	int y;
	// 이동 비용
	float cost;
	DirectionType type;
};

class Node
{
public:
	Node(int x, int y, Node* parentNode = nullptr)
		:position(x, y), parent(parentNode)
	{
	}

	Position operator-(const Node& other)
	{
		return Position(position.x - other.position.x, position.y - other.position.y);
	}

	bool operator==(const Node& other) const 
	{
		return position.x == other.position.x && position.y == other.position.y;
	}

public:
	Position position;
	DirectionType direction = DirectionType::Right;
	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;
	Node* parent = nullptr;
};