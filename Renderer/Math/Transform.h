#pragma once
#include "Utils.h"

class Transform
{
public:
	Transform();
	~Transform();

	void Bind();

	XMFLOAT3 GetPosition() const;
	void SetPosition(const XMFLOAT3& newPosition);

	XMFLOAT3 GetRotation() const;
	void SetRotation(const XMFLOAT3& newRotation);

	XMFLOAT3 GetScale() const;
	void SetScale(const XMFLOAT3& newScale);

	XMMATRIX GetWorldMatrix() const;

private:
	void UpdateWorldMatrix();

private:
	ID3D11Buffer* worldTransformBuffer = nullptr;

	//SRT ����
	XMFLOAT3 position;
	XMFLOAT3 rotation;
	XMFLOAT3 scale;
	XMMATRIX worldMatrix;
	bool isDirty = true; //���� �׷������� true
};