#pragma once

#include "Utils.h"
#include "Engine.h"

class Mesh
{
public:
	Mesh();
	//Mesh(void* vertices, uint32 stride, uint32 vertexCount, void* indices, uint32 indexCount);
	virtual ~Mesh();

	void Initialize(void* vertices, uint32 stride, uint32 vertexCount, void* indices, uint32 indexCount);
	virtual void Draw();

protected:
	uint32 vertexCount = 0;
	uint32 indexCount = 0;
	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;
	uint32 stride = 0;
};
