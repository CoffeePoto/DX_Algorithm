#include "RectMesh.h"

RectMesh::RectMesh(XMFLOAT4 color)
{
	VertexType vertices[]
	{
		VertexType{XMFLOAT3(0.48f, 0.48f, 10.0f), color},
		VertexType{XMFLOAT3(0.48f, -0.48f, 10.0f), color},
		VertexType{XMFLOAT3(-0.48f, -0.48f, 10.0f), color},
		VertexType{XMFLOAT3(-0.48f, 0.48f, 10.0f), color}
	};

	vertexCount = _countof(vertices);
	stride = VertexType::Stride();

	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.ByteWidth = VertexType::Stride() * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexBufferData = {};
	vertexBufferData.pSysMem = vertices;

	HRESULT result = Engine::Get().GetDevice()->CreateBuffer(
		&vertexBufferDesc, &vertexBufferData,
		&vertexBuffer
	);
	if (FAILED(result))
	{
		__debugbreak();
		return;
	}

	uint32 indices[]
	{
		0, 1, 2,
		0, 2, 3
	};
	indexCount = _countof(indices);

	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.ByteWidth = sizeof(uint32) * indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA indexBufferData = {};
	indexBufferData.pSysMem = indices;

	result = Engine::Get().GetDevice()->CreateBuffer(
		&indexBufferDesc, &indexBufferData,
		&indexBuffer
	);
	if (FAILED(result))
	{
		__debugbreak();
		return;
	}
}

RectMesh::~RectMesh()
{
}
