#include "Mesh.h"

Mesh::Mesh(void* vertices, uint32 stride, uint32 vertexCount, void* indices, uint32 indexCount)
	:vertexCount(vertexCount), stride(stride), indexCount(indexCount)
{
	//1.vertexbuffer 설정
	D3D11_BUFFER_DESC vertexDesc = {};
	vertexDesc.ByteWidth = stride * vertexCount;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexBufferData = {};
	vertexBufferData.pSysMem = vertices;

	HRESULT result = Engine::Get().GetDevice()->CreateBuffer(
		&vertexDesc, &vertexBufferData, &vertexBuffer
	);

	if (FAILED(result))
	{
		__debugbreak();
		return;
	}

	D3D11_BUFFER_DESC indexDesc = {};
	indexDesc.ByteWidth = sizeof(uint32) * indexCount;
	indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA indexBufferData = {};
	indexBufferData.pSysMem = indices;

	result = Engine::Get().GetDevice()->CreateBuffer(
		&indexDesc, &indexBufferData, &indexBuffer
	);
	if (FAILED(result))
	{
		__debugbreak();
		return;
	}
}

Mesh::~Mesh()
{
}

void Mesh::Draw()
{
	//Input Assembler에 조립
	//uint32 stride = sizeof(VertexType);
	uint32 offset = 0;
	Engine::Get().GetContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	Engine::Get().GetContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	Engine::Get().GetContext()->DrawIndexed(indexCount, 0, 0);
}
