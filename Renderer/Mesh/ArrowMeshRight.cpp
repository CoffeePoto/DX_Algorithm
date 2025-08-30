#include "ArrowMeshRight.h"

ArrowMeshRight::ArrowMeshRight(XMFLOAT4 color)
{
	VertexType vertices[] =
	{
		VertexType{XMFLOAT3(0.0f, 0.5f, 10.0f), color},
		VertexType{XMFLOAT3(0.25f, 0.0f, 10.0f), color},
		VertexType{XMFLOAT3(0.0f, -0.5f, 10.0f), color},
		VertexType{XMFLOAT3(0.0f, -0.2f, 10.0f), color},
		VertexType{XMFLOAT3(-0.4f, -0.2f, 10.0f), color},
		VertexType{XMFLOAT3(-0.4f, 0.2f, 10.0f), color},
		VertexType{XMFLOAT3(0.0f, 0.2f, 10.0f), color}
	};
	stride = VertexType::Stride();
	vertexCount = _countof(vertices);

	uint32 indices[] =
	{
		0, 1, 2,
		3, 4, 5,
		3, 5, 6
	};
	indexCount = _countof(indices);

	Mesh::Initialize(vertices, stride, vertexCount, indices, indexCount);
}

ArrowMeshRight::~ArrowMeshRight()
{
}
