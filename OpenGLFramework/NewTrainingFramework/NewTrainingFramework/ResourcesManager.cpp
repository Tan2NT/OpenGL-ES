#include "stdafx.h"
#include "ResourcesManager.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>

char* pathPrefix = "../Resources/";

ResourcesManager::ResourcesManager():
m_modelsCount(0),
m_2DtexturesCount(0),
m_CubeTexturesCount(0),
m_shadersCount(0),
m_pModels(NULL),
m_pShaders(NULL),
m_p2DTextures(NULL)
{
}


ResourcesManager::~ResourcesManager()
{
	delete m_pModels; m_pModels = NULL;
	delete m_p2DTextures; m_p2DTextures = NULL;
	delete m_pShaders; m_pShaders = NULL;
	if (m_pCubeTextures)
	{
		delete m_pCubeTextures; m_pCubeTextures = NULL;
	}
}

void ResourcesManager::Init(char* filePath)
{
	FILE* file = fopen(filePath, "r");
	if (!file)
	{
		esLogMessage("\n Failed to read file %s", filePath);
		return;
	}

	// Read each resources
	int id;
	//Models
	fscanf_s(file, "ModelsCount %d\n", &m_modelsCount);
	m_pModels = new Model[m_modelsCount];
	for (int i = 0; i < m_modelsCount; i++)
	{
		char temp[255];
		fscanf(file, "ID %d\n", &id);	m_pModels[i].SetModelId(id);
		fscanf(file, "FILE \"%s\n", temp);
		temp[strlen(temp) - 1] = '\0';

		char path[80];
		strcpy(path, pathPrefix);
		strcat(path, temp);
		m_pModels[i].Init(path);		
	}
	fscanf(file, "\n");

	//Textures
	std::map<std::string, GLenum> tilingMap;
	tilingMap["GL_CLAMP"] = GL_CLAMP_TO_EDGE;
	tilingMap["GL_REPEAT"] = GL_REPEAT;
	tilingMap["GL_MIRRORED_REPEAT"] = GL_MIRRORED_REPEAT;

	fscanf_s(file, "2DTexturesCount %d\n", &m_2DtexturesCount);
	m_p2DTextures = new Texture[m_2DtexturesCount];
	for (int i = 0; i < m_2DtexturesCount; i++)
	{
		char temp[255];
		fscanf(file, "ID %d\n", &m_p2DTextures[i].m_Id);
		fscanf(file, "FILE \"%s\n", temp);
		temp[strlen(temp) - 1] = '\0';

		char path[80];
		strcpy(path, pathPrefix);
		strcat(path, temp);

		//Tiling
		char tiling[50], tempStr[25];
		fscanf(file, "TILING %s\n", tiling);
		std::map<std::string, GLenum>::iterator it = tilingMap.find(tiling);

		if (it != tilingMap.end())
		{
			m_p2DTextures[i].SetTiling(it->second);
		}else
			m_p2DTextures[i].SetTiling(GL_REPEAT);

		m_p2DTextures[i].Init2DTexture(path);
	}
	fscanf(file, "\n");

	//Cube textures
	fscanf_s(file, "CubeTexturesCount %d\n", &m_CubeTexturesCount);
	m_pCubeTextures = new Texture[m_CubeTexturesCount];
	for (int i = 0; i < m_CubeTexturesCount; i++)
	{
		char temp[255];
		fscanf(file, "ID %d\n", &m_pCubeTextures[i].m_Id);
		fscanf(file, "FILE \"%s\n", temp);
		temp[strlen(temp) - 1] = '\0';

		char path[80];
		strcpy(path, pathPrefix);
		strcat(path, temp);

		//Tiling
		char tiling[50], tempStr[25];
		fscanf(file, "TILING %s\n", tiling);
		std::map<std::string, GLenum>::iterator it = tilingMap.find(tiling);

		if (it != tilingMap.end())
		{
			m_pCubeTextures[i].SetTiling(it->second);
		}
		else
			m_pCubeTextures[i].SetTiling(GL_REPEAT);

		m_pCubeTextures[i].InitCubeTexture(path);
	}
	fscanf(file, "\n");

	//Shaders
	std::map<std::string, GLenum> shaderStatesMap;
	shaderStatesMap["DEPTH_TEST"] = GL_DEPTH_TEST;
	shaderStatesMap["ALPHA"] = GL_ALPHA;
	shaderStatesMap["CULL_FACE"] = GL_CULL_FACE; 
	shaderStatesMap["BLEND"] = GL_BLEND;

	fscanf(file, "ShadersCount %d\n", &m_shadersCount);
	m_pShaders = new Shaders[m_shadersCount];
	for (int i = 0; i < m_shadersCount; i++)
	{
		char temp[255];
		fscanf(file, "ID %d\n", &id); m_pShaders[i].SetShadersId(id);
		fscanf(file, "VS \"%s\n", temp);
		temp[strlen(temp) - 1] = '\0';

		char vertexPath[80];
		strcpy(vertexPath, pathPrefix);
		strcat(vertexPath, temp);

		fscanf(file, "FS \"%s\n", temp);
		temp[strlen(temp) - 1] = '\0';

		char fragmentPath[80];
		strcpy(fragmentPath, pathPrefix);
		strcat(fragmentPath, temp);

		int numshaders;
		fscanf(file, "StatesCount %d\n", &numshaders);
		for (int j = 0; j < numshaders; j++)
		{
			//Tiling
			char state[50];
			fscanf(file, "STATE %s\n", state);

			std::map<std::string, GLenum>::iterator it = shaderStatesMap.find(state);

			if (it != shaderStatesMap.end())
			{
				m_pShaders[i].m_states.push_back(it->second);
			}
			else
				m_pShaders[i].m_states[j] = GL_DEPTH_TEST;
				
		}
		m_pShaders[i].Init(vertexPath, fragmentPath);
	}
}

Texture* ResourcesManager::Get2DTextureById(int id)
{
	for (int i = 0; i < m_2DtexturesCount; i++)
	{
		if (m_p2DTextures[i].m_Id == id)
			return &m_p2DTextures[i];
	}

	return NULL;
}

Texture* ResourcesManager::GetCubeTextureById(int id)
{
	for (int i = 0; i < m_CubeTexturesCount; i++)
	{
		if (m_pCubeTextures[i].m_Id == id)
			return &m_pCubeTextures[i];
	}

	return NULL;
}

Model* ResourcesManager::GetModelById(int id)
{
	for (int i = 0; i < m_modelsCount; i++)
	{
		if (m_pModels[i].GetModelId() == id)
			return &m_pModels[i];
	}

	return NULL;
}

Shaders* ResourcesManager::GetShaderById(int id)
{
	for (int i = 0; i < m_shadersCount; i++)
	{
		if (m_pShaders[i].GetShadersId() == id)
			return &m_pShaders[i];
	}

	return NULL;
}
