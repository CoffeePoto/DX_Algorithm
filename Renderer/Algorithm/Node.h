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
	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;
	Node* parent = nullptr;
};