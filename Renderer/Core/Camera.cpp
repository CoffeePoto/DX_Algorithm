#include "Camera.h"
#include "Engine.h"

Camera::Camera(float fieldOfView, float screenAspect, float width, float height, float zNear, float zFar)
	: fieldofView(fieldOfView), width(width), height(height), zNear(zNear), zFar(zFar)
{
	//뷰 행렬 초기화
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

		// 위쪽을 가리키는 벡터를 설정
		up.x = 0.0f;
		up.y = 1.0f;
		up.z = 0.0f;

		// XMVECTOR 구조체에 로드
		upVector = XMLoadFloat3(&up);

		//카메라 위치 설정
		pos = position;
		positionVector = XMLoadFloat3(&pos);

		// 기본적으로 카메라가 찾고있는 위치를 설정
		lookAt.x = 0.0f;
		lookAt.y = 0.0f;
		lookAt.z = 1.0f;

		// XMVECTOR 구조체에 로드
		lookAtVector = XMLoadFloat3(&lookAt);

		// yaw (Y 축), pitch (X 축) 및 roll (Z 축)의 회전값을 라디안 단위로 설정합니다.
		pitch = rotation.x * 0.0174532925f;
		yaw = rotation.y * 0.0174532925f;
		roll = rotation.z * 0.0174532925f;

		// 마지막으로 세 개의 업데이트 된 벡터에서 뷰 행렬을 만듭니다.
		viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
	}
	//if문 안 묶음
	CameraBuffer cameraBufferData;
	cameraBufferData.viewMatrix = XMMatrixTranspose(viewMatrix);
	cameraBufferData.projectionMatrix = XMMatrixTranspose(projectionMatrix);

	D3D11_SUBRESOURCE_DATA bufferData = {};
	bufferData.pSysMem = &cameraBufferData;

	Engine::Get().GetContext()->UpdateSubresource(
		cameraBuffer, 0, nullptr, &cameraBufferData, 0, 0
	);

	//1번 버퍼에 값 전달
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
