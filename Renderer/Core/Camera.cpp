#include "Camera.h"
#include "Engine.h"

Camera::Camera(float fieldOfView, float screenAspect, float width, float height, float zNear, float zFar)
	: fieldofView(fieldOfView), width(width), height(height), zNear(zNear), zFar(zFar)
{
	//�� ��� �ʱ�ȭ
	viewMatrix = XMMatrixIdentity();
	projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, width / height, zNear, zFar);

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.ByteWidth = sizeof(CameraBuffer);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	CameraBuffer cameraBufferData;
	cameraBufferData.viewMatrix = XMMatrixTranspose(viewMatrix);
	cameraBufferData.projectionMatrix = XMMatrixTranspose(projectionMatrix);

	D3D11_SUBRESOURCE_DATA bufferData = {};
	bufferData.pSysMem = &cameraBufferData;

	HRESULT result = Engine::Get().GetDevice()->CreateBuffer
	(
		&bufferDesc, &bufferData, &cameraBuffer
	);
	if (FAILED(result))
	{
		__debugbreak();
		return;
	}
}

Camera::~Camera()
{
	SafeRelease(cameraBuffer);
}

void Camera::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	isDirty = true;
}

void Camera::SetRotation(float x, float y, float z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
	isDirty = true;
}

XMFLOAT3 Camera::GetPosition()
{
	return position;
}

XMFLOAT3 Camera::GetRotation()
{
	return rotation;
}

void Camera::Render()
{
	if (isDirty)
	{
		XMFLOAT3 up, pos, lookAt;
		XMVECTOR upVector, positionVector, lookAtVector;
		float yaw, pitch, roll;
		//XMMATRIX rotationMatrix;

		// ������ ����Ű�� ���͸� ����
		up.x = 0.0f;
		up.y = 1.0f;
		up.z = 0.0f;

		// XMVECTOR ����ü�� �ε�
		upVector = XMLoadFloat3(&up);

		//ī�޶� ��ġ ����
		pos = position;
		positionVector = XMLoadFloat3(&pos);

		// �⺻������ ī�޶� ã���ִ� ��ġ�� ����
		lookAt.x = 0.0f;
		lookAt.y = 0.0f;
		lookAt.z = 1.0f;

		// XMVECTOR ����ü�� �ε�
		lookAtVector = XMLoadFloat3(&lookAt);

		// yaw (Y ��), pitch (X ��) �� roll (Z ��)�� ȸ������ ���� ������ �����մϴ�.
		pitch = rotation.x * 0.0174532925f;
		yaw = rotation.y * 0.0174532925f;
		roll = rotation.z * 0.0174532925f;

		// ���������� �� ���� ������Ʈ �� ���Ϳ��� �� ����� ����ϴ�.
		viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
	}
	//if�� �� ����
	CameraBuffer cameraBufferData;
	cameraBufferData.viewMatrix = XMMatrixTranspose(viewMatrix);
	cameraBufferData.projectionMatrix = XMMatrixTranspose(projectionMatrix);

	D3D11_SUBRESOURCE_DATA bufferData = {};
	bufferData.pSysMem = &cameraBufferData;

	Engine::Get().GetContext()->UpdateSubresource(
		cameraBuffer, 0, nullptr, &cameraBufferData, 0, 0
	);

	//1�� ���ۿ� �� ����
	Engine::Get().GetContext()->VSSetConstantBuffers(1, 1, &cameraBuffer);
}

XMMATRIX Camera::GetViewMatrix()
{
	return viewMatrix;
}

XMMATRIX Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}
