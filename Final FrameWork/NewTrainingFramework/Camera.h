#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Globals.h"
#include "Singleton.h"
#include <conio.h>
#include "InputManager.h"
class Camera
{
	bool m_isUpdate;
public:
	Vector3 mPosition, moveL, mRotate;
	Matrix mView, mWorld, mProject;
	float rotSpeed, tranSpeed;
	float rotAngleX, rotAngleY;
	float fogStart, fogLength;
	
	Camera(void);
	void Init();
	void Update(float deltaTime);
	void SetSpeed(float);
	void MoveRight(float deltaTime);
	void MoveLeft(float deltaTime);
	void MoveForward(float deltaTime);
	void MoveBackward(float deltaTime);
	void RotateRight(float deltaTime);
	void RotateLeft(float deltaTime);
	void RotateUp(float deltaTime);
	void RotateDown(float deltaTime);
	Matrix CalculateWorldMatrix();
	Matrix CalculateViewMatrix();
	~Camera(void);
};
