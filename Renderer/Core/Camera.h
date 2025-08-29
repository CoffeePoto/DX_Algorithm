#pragma once
#include "Utils.h"

using namespace DirectX;

struct CameraBuffer
{
	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;
};

class Camera
{
public:
	Camera(float fieldOfView, float screenAspect, float width, float height, float zNear, float zFar);
	~Camera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render();

	XMMATRIX GetViewMatrix();
	XMMATRIX GetProjectionMatrix();

private:
	XMFLOAT3 position = { 0.f, 0.f, 0.f };
	XMFLOAT3 rotation = { 0.f, 0.f, 0.f };
	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;
	ID3D11Buffer* cameraBuffer = nullptr;

	float zNear = 0.0f;
	float zFar = 0.0f;
	float width = 0.0f;
	float height = 0.0f;
	float fieldofView = 0.0f;
	bool isDirty = true;
};