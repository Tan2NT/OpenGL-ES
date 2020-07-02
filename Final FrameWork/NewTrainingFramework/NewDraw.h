#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include "Camera.h"
#include "GCamera.h"
#include "Model.h"
#include "Texture.h"

class NewDraw
{
public:
	GLuint vboId1;
	GLuint vIndice;
	GLuint TexID;
	int numberOfIndice;
	Shaders myShaders1;

	Matrix m_project, m_world, m_view, m_mvp;
	Matrix m_tran, m_scale, m_rotate, m_rotx, m_roty, m_rotz;
	Vector3 v_sale, v_rotate, v_translate;


	Vertex* vertexData;
	int* indiceData;

	Camera* myCamera;
	GCamera* gCamera;
	Model* gModel;
	Texture* gTexture;

	NewDraw(void);
	int Init( ESContext *esContext);
	void Render(ESContext *esContext);
	void Update ( ESContext *esContext, float deltaTime );
	void Key ( ESContext *esContext, unsigned char key, bool bIsPressed);
	~NewDraw(void);
};
