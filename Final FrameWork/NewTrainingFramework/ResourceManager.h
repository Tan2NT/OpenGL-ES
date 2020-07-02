#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include "Model.h"
#include "Texture.h"
#include "Singleton.h"
#include "CubeTexture.h"

class ResoureManager : public Singleton<ResoureManager>
{
public:
	Shaders* listShaders;
	Model* listModels;
	Texture* listTextures;
	CubeTexture* listCubes;

	int modelCount;
	int texture2DCount;
	int texCubeCount;
	int shaderCount;

	ResoureManager(void);
	Texture* GetTexture(int id);
	Model* GetModel(int id);
	Shaders* GetShader(int id);
	CubeTexture* GetCube(int id);
	 
	void Init(const char* filePath);
	~ResoureManager(void);
};
