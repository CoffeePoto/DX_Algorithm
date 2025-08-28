#include "Camera.h"

Camera::Camera()
{
	viewMatrix = XMMatrixIdentity();
}

Camera::~Camera()
{
}

void Camera::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y - y;
	position.z = z;
}

void Camera::SetRotation(float x, float y, float z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
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
	XMFLOAT3 up, pos, lookAt;
	XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	XMMATRIX rotationMatrix;

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

	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// lookAt 및 up 벡터를 회전 행렬로 변형하여 뷰가 원점에서 올바르게 회전되도록 합니다.
	lookAtVector = XMVector3TransformNormal(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformNormal(upVector, rotationMatrix);

	// 회전 된 카메라 위치를 뷰어 위치로 변환합니다.
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	// 마지막으로 세 개의 업데이트 된 벡터에서 뷰 행렬을 만듭니다.
	viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

}

XMMATRIX Camera::GetViewMatrix()
{
	return viewMatrix;
}