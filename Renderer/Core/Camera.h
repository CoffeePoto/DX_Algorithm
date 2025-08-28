#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render();
	XMMATRIX GetViewMatrix();

private:
	XMFLOAT3 position = { 0.f, 0.f, 0.f };
	XMFLOAT3 rotation = { 0.f, 0.f, 0.f };
	XMMATRIX viewMatrix;
};