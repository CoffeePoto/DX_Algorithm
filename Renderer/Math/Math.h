#pragma once


struct Vector3
{
	Vector3(float x, float y, float z)
		:x(x), y(y), z(z)
	{
	}

	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
};

struct Color
{
	Color(float r, float g, float b, float a)
		:r(r), g(g), b(b), a(a)
	{
	}

	float r = 0.f;
	float g = 0.f;
	float b = 0.f;
	float a = 0.f;
};

struct VertexType
{
	Vector3 position;
	Color color;

	static unsigned int Stride() { return sizeof(VertexType); }
};
