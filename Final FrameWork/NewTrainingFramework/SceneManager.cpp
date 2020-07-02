#pragma once
#include "StdAfx.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Light.h"
extern Camera *sceneCamera;
SceneManager::SceneManager(void)
{
	listObject = 0;

	/*fontArialMS = 0;
	fontArialMS = new FontGame();

	fontArialMS->InitFontTexture("../Resources/Textures/ArialMS.tga");
	fontArialMS->LoadFontData("../Resources/Model/ArialMS.fnt");*/
}

void SceneManager::Init(const char* filePath)
{
	ifstream smFile;
	smFile.open(filePath);
	if(smFile)
	{
		cout<<"file Scene Manager.txt is found "<<"\n";
		while(!smFile.eof())
		{
			string lineData;
			getline(smFile, lineData);
			if(lineData.find(string("#Objects:")) == 0)
			{
				sscanf_s(lineData.data(), "#Objects: %d", &objectCount);
				listObject = new Object[objectCount];

				for(int i = 0; i < objectCount; i++)
				{
					listObject[i].Init();
					getline(smFile, lineData);
					int id, modelID, texturesCount, shadersID;
					Vector3 v_pos, v_rot, v_scale;

					//Read Model
					getline(smFile, lineData);
					sscanf_s(lineData.data(), "ID %d", &id);

					getline(smFile, lineData);
					sscanf_s(lineData.data(), "MODEL %d", &modelID);
					listObject[i].mModel = ResoureManager::GetInstance()->GetModel(modelID);

					// Read Texture
					getline(smFile, lineData);
					sscanf_s(lineData.data(), "ID %d", &id);
					sscanf_s(lineData.data(), "TEXTURES %d", &texturesCount);
					listObject[i].tex2DCount = texturesCount;
					for(int j = 0; j < texturesCount; j++)
					{
						int textureID;
						getline(smFile, lineData);
						sscanf_s(lineData.data(), "TEXTURE %d", &textureID);
						listObject[i].mTexture[j] = ResoureManager::GetInstance()->GetTexture(textureID);
					}

					//Read Cubetextures
					getline(smFile, lineData);
					sscanf_s(lineData.data(), "CUBETEXTURES %d", &listObject[i].texCubeCount);
					for(int j = 0; j < listObject[i].texCubeCount; j++)
					{
						int cubeID;
						getline(smFile, lineData);
						sscanf_s(lineData.data(), "CUBETEXTURE %d", &cubeID);
						listObject[i].mCube[j] = ResoureManager::GetInstance()->GetCube(cubeID);
					}

					//Read Shader
					getline(smFile, lineData);
					sscanf_s(lineData.data(), "SHADER %d", &shadersID);
					listObject[i].mShaders = ResoureManager::GetInstance()->GetShader(shadersID);

					//REad Lights
					getline(smFile, lineData);
					sscanf_s(lineData.data(), "LIGHTS %d", &listObject[i].lightCount);
					for(int j = 0; j < listObject[i].lightCount; j++)
					{
						getline(smFile, lineData);
					}

					//Read Postion - Rotation - Scale Vectors
					getline(smFile, lineData);
					sscanf_s(lineData.data(), "POSITION %f, %f, %f", &v_pos.x, &v_pos.y, &v_pos.z);
					listObject[id].SetTranlation(v_pos);

					getline(smFile, lineData);
					sscanf_s(lineData.data(), "ROTATION %f, %f, %f", &v_rot.x, &v_rot.y, &v_rot.z);
					listObject[id].SetRotation(v_rot);

					getline(smFile, lineData);
					sscanf_s(lineData.data(), "SCALE %f, %f, %f", &v_scale.x, &v_scale.y, &v_scale.z);
					listObject[id].SetScale(v_scale);
				}
			}

			if(lineData.find(string("#LIGHT")) == 0)
			{
				//Read Light
				getline(smFile, lineData);			
				sscanf_s(lineData.data(), "AmbientColor %f, %f, %f", &Light::GetInstance()->mAmbientColor.x, &Light::GetInstance()->mAmbientColor.y, &Light::GetInstance()->mAmbientColor.z);

				getline(smFile, lineData);
				sscanf_s(lineData.data(), "AMbientWeight %f", &Light::GetInstance()->mAmbientWeight);

				getline(smFile, lineData);
				sscanf_s(lineData.data(), "LightsCount %d", &Light::GetInstance()->Light::GetInstance()->mLightsCount);

				if(Light::GetInstance()->mLightsCount > 0)
				{
					Light::GetInstance()->Init(Light::GetInstance()->mLightsCount);
				}

				for(int i = 0; i < Light::GetInstance()->mLightsCount; i++)
				{
					getline(smFile, lineData);
					int id;
					float radius, speed, specPower;
					Vector3 position, diffuseColor, specularColor;
					string szType, szMoving;
					const char *type, *moving;

					getline(smFile, lineData);
					sscanf_s(lineData.data(), "ID %d", &id);

					getline(smFile, lineData);
					sscanf_s(lineData.data(), "POS/DIR %f, %f, %f", &position.x, &position.y, &position.z);

					getline(smFile, szType);
					type = szType.c_str();
					type += 5;

					getline(smFile, lineData);
					sscanf_s(lineData.data(), "DIFFUSE COLOR %f, %f, %f", &diffuseColor.x, &diffuseColor.y, &diffuseColor.z);

					getline(smFile, lineData);
					sscanf_s(lineData.data(), "SPECULAR COLOR %f, %f, %f", &specularColor.x, &specularColor.y, &specularColor.z);

					getline(smFile, lineData);
					sscanf_s(lineData.data(), "SPECULAR POWER %f", &specPower);

					getline(smFile, szMoving);
					moving = szMoving.c_str();
					moving += 7;

					getline(smFile, lineData);
					sscanf_s(lineData.data(), "RADIUS %f", &radius);

					getline(smFile, lineData);
					sscanf_s(lineData.data(), "SPEED %f", &speed);

					Light::GetInstance()->InitLight(id, position, diffuseColor, specularColor, specPower, type, moving, radius, speed); 
				}
			}

			if(lineData.find(string("#CAMERA")) == 0)
			{
				float cNear, cFar, cFov, cSpeed;
				//Read Camera
				getline(smFile, lineData);
				sscanf_s(lineData.data(), "NEAR %f", &cNear);

				getline(smFile, lineData);
				sscanf_s(lineData.data(), "FAR %f", &cFar);

				getline(smFile, lineData);
				sscanf_s(lineData.data(), "FOV %f", &cFov);

				getline(smFile, lineData);
				sscanf_s(lineData.data(), "SPEED %f", &cSpeed);

				sceneCamera->SetSpeed(cSpeed);
				sceneCamera->mProject.SetPerspective(cFov, Globals::screenWidth / Globals::screenHeight, cNear, cFar);

				getline(smFile, lineData);
				sscanf_s(lineData.data(), "Fog Start %f", &sceneCamera->fogStart);

				getline(smFile, lineData);
				sscanf_s(lineData.data(), "Fog Length %f", &sceneCamera->fogLength);
			}
		}
		smFile.close();
	}
	else
	{
		cout<<"file Scene Manager.txt is not found "<<"\n";
	}
}

void SceneManager::Render()
{
	// Render to Frame buufer
	glBindFramebuffer(GL_FRAMEBUFFER, EffectManager::GetInstance()->mListFbo[0].fboId);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for(int i = 0; i < objectCount; i++)
	{
		listObject[i].Render();
	}

	//fontArialMS->DrawString(3.0f, 3.0f, 0.2f, 0.3f, 0.2f, "THIS IS STRING");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	EffectManager::GetInstance()->Render(EffectManager::GetInstance()->mCurrentEffect);
}


void SceneManager::Update(float deltaTime)
{
	for(int i = 0; i <= objectCount; i ++)
	{
		listObject[i].Update(deltaTime);
	}

	EffectManager::GetInstance()->Update();
}

SceneManager::~SceneManager(void)
{
	if(listObject != 0)
	{
		delete[] listObject;
		listObject = 0;
	}
}
