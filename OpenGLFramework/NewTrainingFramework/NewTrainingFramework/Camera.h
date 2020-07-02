#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"

#define ROTATE_LIMITED 1.5707

class Camera
{
	Vector3	m_position;
	Vector3 m_rotation;
	float	m_rotSpeed, m_moveSpeed;
	float	m_nearPlane, m_farPlane, m_fov, m_aspect;
	Matrix	m_worldMatrix, m_viewMatrix, m_projectionMatrix;
	bool	m_shouldCameraMatrixs;
public:
	Camera();
	~Camera();

	void Init(float fovy, float aspect, float nearPlane, float farPlane, float moveSpeed, float rotSpeed);

	void	SetPosition(Vector3 pos)			{ m_position = pos; };
	void	SetRotation(Vector3 rot)			{ m_rotation = rot; };
	void	SetMoveSpeed(float moveSpeed)		{ m_moveSpeed = moveSpeed; }
	void	SetRotationSpeed(float rotSpeed)	{ m_rotSpeed = rotSpeed; }
	void	SetFovy(float fovy)					{ m_fov = fovy; }
	void	SetAspect(float aspect)				{ m_aspect = aspect; }
	void	SetNearPlane(float nearPlane)		{ m_nearPlane = nearPlane; }
	void	SetFarPlane(float farPlane)			{ m_farPlane = farPlane; }

	//Methods to move the camera: forward, backward, left, right
	void	MoveForward(float deltaTime);
	void	MoveBackward(float deltaTime);
	void	MoveLeft(float deltaTime);
	void	MoveRight(float deltaTime);
	void	MoveUp(float deltaTime);
	void	MoveDown(float deltaTime);

	//Methods to rotate the camera: up, down, left, right
	void	RotateUp(float deltaTime);
	void	RotateDown(float deltaTime);
	void	RotateLeft(float deltaTime);
	void	RotateRight(float deltaTime);

	// World and view matrix
	void	HandleKeyInput(unsigned char keyCode, float deltaTime);
	void	UpdateWorldMatrix();
	void	UpdateViewMatrix();
	void	UpdateProjectionMatrix();
	Matrix	GetWorldMatrix()		{ return m_worldMatrix; };
	Matrix	GetViewMatrix()			{ return m_viewMatrix; };
	Matrix	GetProjectionMatrix()	{ return m_projectionMatrix; };
};

