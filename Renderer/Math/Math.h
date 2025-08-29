#pragma once
#include <DirectXMath.h>
using namespace DirectX;

struct VertexType
{
	XMFLOAT3 position;
	XMFLOAT4 color;

	static unsigned int Stride() { return sizeof(VertexType); }
};
