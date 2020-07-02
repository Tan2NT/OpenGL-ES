#pragma once
#include "Shaders.h"
#include "Texture.h"
#include "Model.h"
#include "stdafx.h"
#include "Singleton.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

class ResourcesManager : public SingletonTemplate<ResourcesManager>
{
	Model		*m_pModels;
	Texture		*m_p2DTextures;
	Texture		*m_pCubeTextures;
	Shaders		*m_pShaders;

	int			m_modelsCount, m_2DtexturesCount, m_shadersCount, m_CubeTexturesCount;

public:
	ResourcesManager();
	~ResourcesManager();

	void		Init(char* filePath);

	Texture*	Get2DTextureById(int id);
	Texture*	GetCubeTextureById(int id);
	Model*		GetModelById(int id);
	Shaders*	GetShaderById(int id);

};

inline ResourcesManager* GetResourcesManager()
{
	return ResourcesManager::GetInstance();
}

