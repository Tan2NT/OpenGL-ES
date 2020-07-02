#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Texture.h"
#include "Model.h"
#include "Shaders.h"

class GameObject
{
	int			m_objectId;
	
	// Materials
	Model		*m_model;
	int			m_numOfTextures;
	Texture		**m_textures;
	Shaders		*m_shader;

	// transform
	Vector3		m_translate;
	Vector3		m_scale;
	Vector3		m_rotate;
	float		m_moveSpeed;

public:
	GameObject();
	~GameObject();
	void		SetModel(Model *model);
	void		SetTextures(Texture** textures, int numTexs);
	void		SetShader(Shaders* shader);

	int			GetId() { return m_objectId; }

	void		Init(Model *model, Texture **texture, int numTexs, Shaders *shader);
	void		Update(float deltaTime);
	void		Draw(ESContext *esContext);

	void		SetScale(Vector3 scale);
	void		SetTranslate(Vector3 tran);
	void		SetRotate(Vector3 rot);
	Matrix		CalculateMVPMatrix();
	Matrix		CalculateWorldMatrix();

	void		MoveLeft(float deltaTime);
	void		MoveRight(float deltaTime);
	void		MoveForward(float deltaTime);
	void		MoveBackward(float deltaTime);
	void		MoveUp(float deltaTime);
	void		MoveDown(float deltaTime);

	void	HandleInput(unsigned char keyCode, float deltaTime);
};

