#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	m_position = Vector3(0.0, 0.0, 10.0);
	m_rotation = Vector3(0.0, 0.0, 0.0);
	m_worldMatrix.SetIdentity();
	m_viewMatrix.SetIdentity();
	m_projectionMatrix.SetIdentity();
}


Camera::~Camera()
{
}

void Camera::Init(float fovy, float aspect, float nearPlane, float farPlane, float moveSpeed, float rotSpeed)
{
	SetFovy(fovy);
	SetAspect(aspect);
	SetNearPlane(nearPlane);
	SetFarPlane(farPlane);
	SetMoveSpeed(moveSpeed);
	SetRotationSpeed(rotSpeed);

	UpdateWorldMatrix();
	UpdateViewMatrix();
	UpdateProjectionMatrix();
}

void Camera::MoveForward(float deltaTime)
{
	Vector4 moveL = Vector4(0.0f, 0.0f, -m_moveSpeed * deltaTime, 1.0);
	Vector4 moveW = moveL * m_worldMatrix;
	m_position = Vector3(moveW.x, moveW.y, moveW.z);
	UpdateWorldMatrix();
	UpdateViewMatrix();
}

void Camera::MoveBackward(float deltaTime)
{
	Vector4 moveL = Vector4(0.0f, 0.0f, m_moveSpeed * deltaTime, 1.0);
	Vector4 moveW = moveL * m_worldMatrix;
	m_position = Vector3(moveW.x, moveW.y, moveW.z);
	UpdateWorldMatrix();
	UpdateViewMatrix();
}

void Camera::MoveLeft(float deltaTime)
{
	Vector4 moveL = Vector4(m_moveSpeed * deltaTime, 0.0f, 0.0f, 1.0);
	Vector4 moveW = moveL * m_worldMatrix;
	m_position = Vector3(moveW.x, moveW.y, moveW.z);
	UpdateWorldMatrix();
	UpdateViewMatrix();
}

void Camera::MoveRight(float deltaTime)
{
	Vector4 moveL = Vector4(-m_moveSpeed * deltaTime, 0.0f, 0.0f, 1.0);
	Vector4 moveW = moveL * m_worldMatrix;
	m_position = Vector3(moveW.x, moveW.y, moveW.z);
	UpdateWorldMatrix();
	UpdateViewMatrix();
}

void Camera::MoveUp(float deltaTime)
{
	Vector4 moveL = Vector4(0.0f, -m_moveSpeed * deltaTime, 0.0f, 1.0);
	Vector4 moveW = moveL * m_worldMatrix;
	m_position = Vector3(moveW.x, moveW.y, moveW.z);
	UpdateWorldMatrix();
	UpdateViewMatrix();
}

void Camera::MoveDown(float deltaTime)
{
	Vector4 moveL = Vector4(0.0f, m_moveSpeed * deltaTime, 0.0f, 1.0);
	Vector4 moveW = moveL * m_worldMatrix;
	m_position = Vector3(moveW.x, moveW.y, moveW.z);
	UpdateWorldMatrix();
	UpdateViewMatrix();
}

void Camera::RotateUp(float deltaTime)
{
	m_rotation.x += m_rotSpeed * deltaTime;
	UpdateWorldMatrix();
	UpdateViewMatrix();
}

void Camera::RotateDown(float deltaTime)
{
	m_rotation.x -= m_rotSpeed * deltaTime;
	UpdateWorldMatrix();
	UpdateViewMatrix();
}

void Camera::RotateLeft(float deltaTime)
{
	m_rotation.y += m_rotSpeed * deltaTime;
	UpdateWorldMatrix();
	UpdateViewMatrix();
}

void Camera::RotateRight(float deltaTime)
{
	m_rotation.y -= m_rotSpeed * deltaTime;
	UpdateWorldMatrix();
	UpdateViewMatrix();
}

void Camera::HandleKeyInput(unsigned char keyCode, float deltaTime)
{
	switch (keyCode)
	{
	case KEY_CAMERA_MOVE_LEFT:
		MoveLeft(deltaTime);
		break;
	case KEY_CAMERA_MOVE_RIGHT:
		MoveRight(deltaTime);
		break;
	case KEY_CAMERA_MOVE_FORWARD:
		MoveForward(deltaTime);
		break;
	case KEY_CAMERA_MOVE_BACKWARD:
		MoveBackward(deltaTime);
		break;
	case KEY_CAMERA_MOVE_UP:
		MoveUp(deltaTime);
		break;
	case KEY_CAMERA_MOVE_DOWN:
		MoveDown(deltaTime);
		break;
	case KEY_CAMERA_ROTATE_LEFT:
		RotateLeft(deltaTime);
		break;
	case KEY_CAMERA_ROTATE_RIGHT:
		RotateRight(deltaTime);
		break;
	case KEY_CAMERA_ROTATE_UP:
		RotateUp(deltaTime);
		break;
	case KEY_CAMERA_ROTATE_DOWN:
		RotateDown(deltaTime);
		break;
	default:
		break;
	}
}


void Camera::UpdateWorldMatrix()
{
	Matrix matRotZ, matRotX, matRotY, matTrans;
	matRotZ.SetRotationZ(m_rotation.z);
	matRotX.SetRotationX(m_rotation.x);
	matRotY.SetRotationY(m_rotation.y);
	matTrans.SetTranslation(m_position);
	m_worldMatrix = matRotZ *matRotX * matRotY * matTrans;
}

void Camera::UpdateViewMatrix()
{
	m_viewMatrix = m_worldMatrix.Inverse();
}

void Camera::UpdateProjectionMatrix()
{
	m_projectionMatrix.SetPerspective(m_fov, m_aspect, m_nearPlane, m_farPlane);
}