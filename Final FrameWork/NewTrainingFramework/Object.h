#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include "Model.h"
#include "Texture.h"
#include "Camera.h"
#include "CubeTexture.h"
#include "ResourceManager.h"
#include "Light.h"
#include "InputManager.h"

class Object
{
private:
	Vector3 mScale, mRotate, mPosition;
public:
	int tex2DCount, texCubeCount, lightCount;
	Matrix m_project;

	Vertex* vertexData;
	int* indiceData;

	Model *mModel;
	Texture *mTexture[MAX_TEXTURE];
	Shaders *mShaders;
	CubeTexture *mCube[MAX_CUBE_TEXTURE];

	void SetTranlation( Vector3);
	void SetRotation( Vector3);
	void SetScale( Vector3);

	void Init();
	void Render();
	void Update( float deltaTime );
	void Key( ESContext *esContext, unsigned char key, bool bIsPressed);
	Matrix CalculateWorldMatrix();
	void SendAttribute();
	void SendLight();
	void SendTexture();
	void SendRest();

	Object(void);
	~Object(void);
};
