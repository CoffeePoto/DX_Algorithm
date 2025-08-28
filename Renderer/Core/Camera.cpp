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

	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// lookAt �� up ���͸� ȸ�� ��ķ� �����Ͽ� �䰡 �������� �ùٸ��� ȸ���ǵ��� �մϴ�.
	lookAtVector = XMVector3TransformNormal(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformNormal(upVector, rotationMatrix);

	// ȸ�� �� ī�޶� ��ġ�� ��� ��ġ�� ��ȯ�մϴ�.
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	// ���������� �� ���� ������Ʈ �� ���Ϳ��� �� ����� ����ϴ�.
	viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

}

XMMATRIX Camera::GetViewMatrix()
{
	return viewMatrix;
}