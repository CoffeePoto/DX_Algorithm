#include "StartMesh.h"

StartMesh::StartMesh()
{
	VertexType vertices[] =
	{
		VertexType{XMFLOAT3(0.5f, 0.5f, 2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		VertexType{XMFLOAT3(0.5f, -0.5f, 2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		VertexType{XMFLOAT3(-0.5f, -0.5f, 2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		VertexType{XMFLOAT3(-0.5f, 0.5f, 2.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)}
	};
	uint32 stride = VertexType::Stride();
	uint32 vertexCount = _countof(vertices);

	uint32 indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};
	uint32 indexCount = _countof(indices);

	Initialize(vertices, stride, vertexCount, indices, indexCount);
}

StartMesh::~StartMesh()
{
}
