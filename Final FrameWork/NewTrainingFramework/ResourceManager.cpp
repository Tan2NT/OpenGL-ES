#include "StdAfx.h"
#include "ResourceManager.h"

ResoureManager::ResoureManager(void)
{
}

void ResoureManager::Init(const char *filePath)
{
	ifstream fileRM;
	fileRM.open(filePath);
	if(fileRM.is_open())
	{
		cout<<"file Resource Manager.txt id open "<<"\n";
 		while(!fileRM.eof())
		{
			string lineData;
			getline(fileRM, lineData);
			if(!lineData.empty())
			{
				// Read Model
				if(lineData.find(string("#Models:")) == 0)
				{
					sscanf_s(lineData.data(), "#Models: %d", &modelCount);
					cout<<"num Models: "<<modelCount<<"\n";
					listModels = new Model[modelCount];

					for(int i = 0; i < modelCount; i++)
					{
						string modelID, modelPath;
						const char* path;
						int id;
						getline(fileRM, modelID);
						getline(fileRM, modelPath);
						
						sscanf_s(modelID.data(), "ID %d", &id);
						path = modelPath.c_str();
						path += 5;
						listModels[i].Init(path);
						listModels[i].id = id;
					}
				}

				//Read Texture
				if(lineData.find(string("#2D Textures:")) == 0)
				{
					sscanf_s(lineData.data(), "#2D Textures: %d", &texture2DCount);
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
						
						sscanf_s(szID.data(), "ID %d", &id);
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
					sscanf_s(lineData.data(), "#Cube Textures: %d", &texCubeCount);
					cout<<"num Textures: "<<texCubeCount<<"\n";
					listCubes = new CubeTexture[texCubeCount];
					for(int i = 0; i < texCubeCount; i++)
					{
						int id;
						getline(fileRM, lineData);
						sscanf_s(lineData.data(), "ID %d", &id);
						const char *skyPath;

						getline(fileRM, lineData);
						skyPath = lineData.c_str();
						skyPath += 5;

						string szTiling;
						const char *tiling;
						getline(fileRM, szTiling);
						tiling = szTiling.c_str();
						tiling += 7;
						unsigned int tilingMode;
						if(strcmp(tiling, "GL_CLAMP_TO_EDGE") == 0)
						{
							tilingMode = GL_CLAMP_TO_EDGE;
						}
						else
						{
							tilingMode = GL_REPEAT;
						}

						listCubes[i].Init(skyPath, tilingMode); 
						listCubes[i].id = id;
					}
				}

				//Read Shader
				if(lineData.find(string("#Shaders:")) == 0)
				{
					sscanf_s(lineData.data(), "#Shaders: %d", &shaderCount);
					cout<<"num shaders: "<<shaderCount<<"\n";
					listShaders = new Shaders[shaderCount];

					for(int i = 0; i < shaderCount; i++)
					{
						string szID, szVertex, szFragment ;
						char *vertexPath, *fragmentPath;
						int id;
						getline(fileRM, szID);
						getline(fileRM, szVertex);
						getline(fileRM, szFragment);
						
						sscanf_s(szID.data(), "ID %d", &id);
						vertexPath = const_cast<char*> (szVertex.c_str());
						vertexPath += 5;
						fragmentPath = const_cast<char*> (szFragment.c_str());
						fragmentPath += 5;
						
						listShaders[i].Init(vertexPath, fragmentPath);
						listShaders[i].id = id;

						int numState;
						string lineText;
						getline(fileRM, lineText);

						sscanf_s(lineText.data(), "STATES %d", &numState);
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
	else
	{
		cout<<"file Resource Manager.txt is not found "<<"\n";
	}
}

Texture* ResoureManager::GetTexture(int id)
{
	int i = 0;
	while((listTextures[i].id != id) && (i < texture2DCount))
	{
		i++;
	}

	if(i >= texture2DCount)
	{
		cout<<" Texture ID = "<< i <<" not found";
		i = 0;
	}
	return	&listTextures[i];
}
Model* ResoureManager::GetModel(int id)
{
	int i = 0;
	while(( listModels[i].id != id) && (i < modelCount))
	{
		i++;
	}

	if(i > modelCount)
	{
		cout<<" Model ID = "<< i <<" not found";

		i = 0;
	}
	return	&listModels[i];
}
Shaders* ResoureManager::GetShader(int id)
{
	int i = 0;
	while(( listShaders[i].id != id) && (i < shaderCount))
	{
		i++;
	}

	if(i > shaderCount)
	{
		cout<<" Shader ID = "<< i <<" not found";
		i = 0;
	}
	return	&listShaders[i];
}

CubeTexture* ResoureManager::GetCube(int id)
{
	int i = 0;
	while(( listCubes[i].id != id) && (i < texCubeCount))
	{
		i++;
	}

	if(i > texCubeCount)
	{
		cout<<" TectureCube ID = "<< i <<" not found";
		i = 0;
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
		listCubes = 0;
	}
}
