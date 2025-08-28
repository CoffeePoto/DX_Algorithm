#include "ObstacleMesh.h"

ObstacleMesh::ObstacleMesh(float bottomx, float bottomy)
{
	//This is for test
	VertexType vertices[]
	{
		VertexType{Vector3(bottomx + 1, bottomy + 1, 20.0f), Color(1.0f, 0.0f, 1.0f, 1.0f)},
		VertexType{Vector3(bottomx + 1, bottomy, 20.0f), Color(1.0f, 0.0f, 1.0f, 1.0f)},
		VertexType{Vector3(bottomx, bottomy, 20.0f), Color(1.0f, 0.0f, 1.0f, 1.0f)},
		VertexType{Vector3(bottomx, bottomy + 1, 20.0f), Color(1.0f, 0.0f, 1.0f, 1.0f)}
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

ObstacleMesh::~ObstacleMesh()
{
}
