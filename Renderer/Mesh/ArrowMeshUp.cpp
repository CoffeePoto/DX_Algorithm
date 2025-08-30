#include "ArrowMeshUp.h"

ArrowMeshUp::ArrowMeshUp(XMFLOAT4 color)
{
	VertexType vertices[]
	{
		VertexType{XMFLOAT3(-0.5f, 0.0f, 10.0f), color},
		VertexType{XMFLOAT3(0.0f, 0.25f, 10.0f), color},
		VertexType{XMFLOAT3(0.5f, 0.0f, 10.0f), color},
		VertexType{XMFLOAT3(-0.2f, 0.0f, 10.0f), color},
		VertexType{XMFLOAT3(-0.2f, -0.4f, 10.0f), color},
		VertexType{XMFLOAT3(0.2f, -0.4f, 10.0f), color},
		VertexType{XMFLOAT3(0.2f, 0.0f, 10.0f), color}
	};
	stride = VertexType::Stride();
	vertexCount = _countof(vertices);

	uint32 indices[]
	{
		0, 1, 2,
		3, 5, 4,
		3, 6, 5
	};
	indexCount = _countof(indices);
	Mesh::Initialize(vertices, stride, vertexCount, indices, indexCount);
}

ArrowMeshUp::~ArrowMeshUp()
{
}
