#include "Transform.h"
#include "Engine.h"

Transform::Transform()
	: position(0.0f, 0.0f, 0.0f),
	rotation(0.0f, 0.0f, 0.0f),
	scale(1.0f, 1.0f, 1.0f)
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = sizeof(XMMATRIX);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	
	UpdateWorldMatrix();
	worldMatrix = XMMatrixTranspose(worldMatrix);

	D3D11_SUBRESOURCE_DATA bufferData = {};
	bufferData.pSysMem = &worldMatrix;

	HRESULT result = Engine::Get().GetDevice()->CreateBuffer
	(
		&bufferDesc, &bufferData, &worldTransformBuffer
	);
	if (FAILED(result))
	{
		__debugbreak();
		return;
	}
}

Transform::~Transform()
{
	SafeRelease(worldTransformBuffer);
}

void Transform::Bind()
{
	if (isDirty)
	{
		UpdateWorldMatrix();
		worldMatrix = XMMatrixTranspose(worldMatrix); //월드 좌표 다시 구했으니 다시 전치
		Engine::Get().GetContext()->UpdateSubresource
		(
			worldTransformBuffer, 0, nullptr, &worldMatrix, 0, 0
		);

		isDirty = false;
	}

	Engine::Get().GetContext()->VSSetConstantBuffers(0, 1, &worldTransformBuffer);

}

XMFLOAT3 Transform::GetPosition() const
{
	return position;
}

void Transform::SetPosition(const XMFLOAT3& newPosition)
{
	position = newPosition;
	isDirty = true;
}

XMFLOAT3 Transform::GetRotation() const
{
	return rotation;
}

void Transform::SetRotation(const XMFLOAT3& newRotation)
{
	rotation = newRotation;
	isDirty = true;
}

XMFLOAT3 Transform::GetScale() const
{
	return scale;
}

void Transform::SetScale(const XMFLOAT3& newScale)
{
	scale = newScale;
	isDirty = true;
}

XMMATRIX Transform::GetWorldMatrix() const
{
	return worldMatrix;
}

void Transform::UpdateWorldMatrix()
{
	//worldmatrix srt 계산진행
	XMMATRIX translationMatrix = XMMatrixTranslation(position.x, position.y, position.z);
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	XMMATRIX scaleMatrix = XMMatrixScaling(scale.x, scale.y, scale.z);
	worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;
}