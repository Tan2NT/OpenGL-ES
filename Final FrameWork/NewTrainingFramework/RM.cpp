#include "StdAfx.h"
#include "RM.h"

ResoureManager::ResoureManager(void)
{
}

void ResoureManager::Init(const char *filePath)
{
	ifstream fileRM;
	fileRM.open(filePath);
	if(fileRM.is_open())
	{
 		while(!fileRM.eof())
		{
			cout<<"file RM.txt id open "<<"\n";
			string lineData;
			getline(fileRM, lineData);
			if(!lineData.empty())
			{
				// Read Model
				if(lineData.find(string("#Models:")) == 0)
				{
					sscanf(lineData.data(), "#Models: %d", &modelCount);
					cout<<"num Models: "<<modelCount<<"\n";
					listModels = new Model[modelCount];

					for(int i = 0; i < modelCount; i++)
					{
						string modelID, modelPath;
						const char* path;
						int id;
						getline(fileRM, modelID);
						getline(fileRM, modelPath);
						
						sscanf(modelID.data(), "ID %d", &id);
						path = modelPath.c_str();
						path += 5;
						listModels[i].Init(path);
						listModels[i].id = id;
					}
				}

				//Read Texture
				if(lineData.find(string("#2D Textures:")) == 0)
				{
					sscanf(lineData.data(), "#2D Textures: %d", &texture2DCount);
					cout<<"num Textures: "<<texture2DCount<<"\n";
					listTextures = new Texture[texture2DCount];
					for(int i = 0; i < texture2DCount; i++)
					{
						string szID, szPath, szTiling ;
						const char *tiling, *path;
						int id;
						unsigned int tilingMode;

						getline(fileRM, szID);
						getline(fileRM, szPath);
						getline(fileRM, szTiling);
						
						sscanf(szID.data(), "ID %d", &id);
						path = szPath.c_str();
						path += 5;
						tiling = szTiling.c_str();
						tiling += 7;

						if(strcmp(tiling, "REPEAT") == 0)
							tilingMode = GL_REPEAT;
						else
							tilingMode = GL_CLAMP_TO_EDGE;

						listTextures[i].Init(path, tilingMode);
						listTextures[i].id = id;
					}
				}

				//Read CubeTextures
				if(lineData.find(string("#Cube Textures:")) == 0)
				{
					sscanf(lineData.data(), "#Cube Textures: %d", &cubeCount);
					cout<<"num Textures: "<<cubeCount<<"\n";
					listCubes = new CubeTexture[cubeCount];
					for(int i = 0; i < cubeCount; i++)
					{
						string szID, szPath, szTiling ;
						const char *tiling, *path;
						int id;
						unsigned int tilingMode;

						getline(fileRM, szID);
						getline(fileRM, szPath);
						getline(fileRM, szTiling);
						
						sscanf(szID.data(), "ID %d", &id);
						path = szPath.c_str();
						path += 5;
						tiling = szTiling.c_str();
						tiling += 7;

						if(strcmp(tiling, "REPEAT") == 0)
							tilingMode = GL_REPEAT;
						else
							tilingMode = GL_CLAMP_TO_EDGE;

						listCubes[i].Init(path, tilingMode);
						listCubes[i].id = id;
					}
				}

				//Read Shader
				if(lineData.find(string("#Shaders:")) == 0)
				{
					sscanf(lineData.data(), "#Shaders: %d", &shaderCount);
					cout<<"num shaders: "<<shaderCount<<"\n";
					listShaders = new Shaders[shaderCount];

					for(int i = 0; i < shaderCount; i++)
					{
						string szID, szVertex, szFragment ;
						char *vertexPath, *fragmentPath;
						int id;
						unsigned int tilingMode;
						getline(fileRM, szID);
						getline(fileRM, szVertex);
						getline(fileRM, szFragment);
						
						sscanf(szID.data(), "ID %d", &id);
						vertexPath = const_cast<char*> (szVertex.c_str());
						vertexPath += 5;
						fragmentPath = const_cast<char*> (szFragment.c_str());
						fragmentPath += 5;
						
						listShaders[i].Init(vertexPath, fragmentPath);
						listShaders[i].id = id;

						int numState;
						string lineText;
						getline(fileRM, lineText);

						sscanf(lineText.data(), "STATES %d", &numState);
						listShaders[i].numState = numState;
						listShaders[i].nState = new unsigned int[numState];
						for(int j = 0; j < numState; j++)
						{
							const char* szState;
							unsigned int stateMode;
							getline(fileRM, lineText);
							szState = lineText.c_str();
							szState += 6;
							if(strcmp(szState, "CULLING") == 0)
							{
								stateMode = GL_CULL_FACE;
							}
							else 
								if(strcmp(szState, "DEPTH_TEST") == 0)
								{
									stateMode = GL_DEPTH_TEST;
								}
								else
									if(strcmp(szState, "ALPHA") == 0)
									{
										stateMode = GL_ALPHA;
									}
									else
									if(strcmp(szState, "BLEND") == 0)
									{
										stateMode = GL_BLEND;
									}
							listShaders[i].nState[j] = stateMode;
						}
					}
				}

			}
		}
	}
}

Texture* ResoureManager::GetTexture(int id)
{
	int i = 0;
	while(listTextures[i].id != id)
	{
		i++;
	}
	return	&listTextures[i];
}
Model* ResoureManager::GetModel(int id)
{
	int i = 0;
	while( listModels[i].id != id)
	{
		i++;
	}
	return	&listModels[i];
}
Shaders* ResoureManager::GetShader(int id)
{
	int i = 0;
	while( listShaders[i].id != id)
	{
		i++;
	}
	return	&listShaders[i];
}

CubeTexture* ResoureManager::GetCube(int id)
{
	int i = 0;
	while( listCubes[i].id != id)
	{
		i++;
	}
	return	&listCubes[i];
}

ResoureManager::~ResoureManager(void)
{
	if(listModels != 0)
	{
		delete[] listModels;
		listModels = 0;
	}
	if(listShaders != 0)
	{
		delete[] listShaders;
		listShaders = 0;
	}
	if(listTextures != 0)
	{
		delete[] listTextures;
		listTextures = 0;
	}

	if(listCubes != 0)
	{
		delete[] listCubes;
		listTextures = 0;
	}
}
