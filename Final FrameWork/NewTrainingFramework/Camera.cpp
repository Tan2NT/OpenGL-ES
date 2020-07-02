#include "StdAfx.h"
#include "Camera.h"

Camera::Camera(void)
{
	moveL = Vector3(0.0f, 0.0f, 0.0f);
	mRotate = Vector3(0.0f, 0.0f, 0.0f);
	rotSpeed = 0.3f, tranSpeed = 3.0f;
	mPosition = Vector3(0.0f, 0.0f, -5.0f);
	rotAngleX = 0;
	rotAngleY = 0;
	mView.SetIdentity();
}

void Camera::Init()
{
	moveL = Vector3(0.0f, 0.0f, 0.0f);
	mRotate = Vector3(0.0f, 0.0f, 0.0f);
	rotSpeed = 0.3f, tranSpeed = 3.0f;
	mPosition = Vector3(0.0f, 0.0f, -5.0f);
	rotAngleX = 0;
	rotAngleY = 0;
	mView.SetIdentity();
}

void Camera::MoveRight(float deltaTime)
{
	Vector3 moveL = Vector3(-tranSpeed * deltaTime, 0.0f, 0.0f);
	//Transform the movement vector from camera’s local space to world space
	Vector4 moveW = Vector4(moveL, 1.0) * CalculateWorldMatrix();

	//Update camera’s position
	mPosition = Vector3(moveW.x, moveW.y, moveW.z);
}

void Camera::MoveLeft(float deltaTime)
{
	Vector3 moveL = Vector3(tranSpeed * deltaTime, 0.0f, 0.0f);
	//Transform the movement vector from camera’s local space to world space
	Vector4 moveW = Vector4(moveL) * CalculateWorldMatrix();

	//Update camera’s position
	mPosition = Vector3(moveW.x, moveW.y, moveW.z);
}

void Camera::MoveForward(float deltaTime)
{
	Vector3 moveL = Vector3(0.0f, 0.0f, -tranSpeed * deltaTime);
	//Transform the movement vector from camera’s local space to world space
	Vector4 moveW = Vector4(moveL) * CalculateWorldMatrix();

	//Update camera’s position
	mPosition = Vector3(moveW.x, moveW.y, moveW.z);
}

void Camera::MoveBackward(float deltaTime)
{
	Vector3 moveL = Vector3(0.0f, 0.0f, tranSpeed * deltaTime);
	//Transform the movement vector from camera’s local space to world space
	Vector4 moveW = Vector4(moveL) * CalculateWorldMatrix();

	//Update camera’s position
	mPosition = Vector3(moveW.x, moveW.y, moveW.z);
}

void Camera::RotateRight(float deltaTime)
{
	mRotate.y += rotSpeed * deltaTime;
}

void Camera::RotateLeft(float deltaTime)
{
	mRotate.y += -rotSpeed * deltaTime;
}

void Camera::RotateUp(float deltaTime)
{
	mRotate.x += rotSpeed * deltaTime;
}

void Camera::RotateDown(float deltaTime)
{
	mRotate.x += -rotSpeed * deltaTime;
}

void Camera::Update(float deltaTime)
{
	InputManager *input = InputManager::GetInstance();
	if(input->is_KeyPressed)
	{
		if(input->IsKeyDown(KEY_A))
		{
			MoveRight(deltaTime);
		}

		if(input->IsKeyDown(KEY_D))
		{
			MoveLeft(deltaTime);			
		}

		if(input->IsKeyDown(KEY_W))
		{
			MoveForward(deltaTime);
		}

		if(input->IsKeyDown(KEY_S))
		{
			MoveBackward(deltaTime);
		}

		if(input->IsKeyDown(KEY_DOWN))
		{
			RotateDown(deltaTime);
		}

		if(input->IsKeyDown(KEY_UP))
		{
			RotateUp(deltaTime);
		}

		if(input->IsKeyDown(KEY_RIGHT))
		{
			RotateRight(deltaTime);
		}

		if(input->IsKeyDown(KEY_LEFT))
		{
			RotateLeft(deltaTime);
		}

		//Calculate View matrix
		mView = CalculateViewMatrix();
	}
	else 
	{
		moveL = Vector3(0.0f, 0.0f, 0.0f);
		mRotate.x += 0;
		mRotate.y += 0;
		rotAngleY = 0;
	}

}

Matrix Camera::CalculateWorldMatrix()
{
	//Calculate World matrix
	Matrix tranMatrix, rotateMatrix, rotXMatrix, rotYMatrix, rotZMatrix;
	rotXMatrix.SetRotationX(mRotate.x);
	rotYMatrix.SetRotationY(mRotate.y);
	rotZMatrix.SetRotationZ(mRotate.z);
	rotateMatrix = rotZMatrix * rotXMatrix * rotYMatrix;
	tranMatrix.SetTranslation(mPosition);
	
	return rotateMatrix * tranMatrix;
}

Matrix Camera::CalculateViewMatrix()
{
	//Calculate ViewMatrix = Invert(World matrix)
	Matrix tranMatrix, rotateMatrix, rotXMatrix, rotYMatrix, rotZMatrix;
	rotXMatrix.SetRotationX(-mRotate.x);
	rotYMatrix.SetRotationY(-mRotate.y);
	rotZMatrix.SetRotationZ(-mRotate.z);
	rotateMatrix = rotYMatrix * rotXMatrix * rotZMatrix;
	tranMatrix.SetTranslation(-mPosition);

	return tranMatrix * rotateMatrix;
}

void Camera::SetSpeed(float cSpeed)
{
	rotSpeed = cSpeed;
}

Camera::~Camera(void)
{
}
