#include "StdAfx.h"
#include "EffectManager.h"

EffectManager::EffectManager(void)
{
	mListShader = 0;
	mListFbo = 0;

	mListEffect = 0;
	mEffectCount = 0;
	mCurrentEffect = Screen;

	mModel = new Model();
	mModel->Init("../Resources/Model/Quad.nfg");
}

void EffectManager::Init(const char *filePath)
{
	ifstream fileEM;
	fileEM.open(filePath);
	if(fileEM)
	{
		cout<<"file Effect Manager.txt is already open "<<"\n";
		while(!fileEM.eof())
		{
			// Read Effect shaders
			string lineData;
			getline(fileEM, lineData);

			if(lineData.find(string("#Shaders:")) == 0)
			{
				sscanf_s(lineData.data(), "#Shaders: %d", &mShaderCount);
				cout<<"\n#Shaders: "<<mShaderCount;
				mListShader = new Shaders[mShaderCount];

				for(int i = 0; i < mShaderCount; i++)
				{
					char *fileVS, *fileFS;
					string vertexFile, fragmentFlie;

					getline(fileEM, lineData);
					sscanf_s(lineData.data(), "ID %d", &mListShader[i].id);
					cout<<"\nID: "<<mListShader[i].id;

					getline(fileEM, vertexFile);
					fileVS	=	const_cast<char*>(vertexFile.c_str());
					fileVS += 8;
					cout<<"\nVSFile: "<<fileVS;

					getline(fileEM, fragmentFlie);
					fileFS	=	const_cast<char*>(fragmentFlie.c_str());
					fileFS += 8;
					cout<<"\nFSFILE: "<<fileFS;

					mListShader[i].Init(fileVS, fileFS);
				}
			}

			// Read Number of Frame buffer objects
			if(lineData.find(string("#FBO")) == 0)
			{
				getline(fileEM, lineData);
				sscanf_s(lineData.data(), "NoFBO %d", &mFboCount);
				cout<<"\nNoFBO "<<mFboCount;
				mListFbo = new FrameBufferObject[mFboCount];

				for(int i = 0; i < mFboCount; i++)
				{
					mListFbo[i].Init();
				}
			}

			//Read Effect
			if(lineData.find(string("#Effects: ")) == 0)
			{
				sscanf_s(lineData.data(), "#Effects: %d", &mEffectCount);
				mListEffect = new Effect[mEffectCount];
				cout<<"\n#Effect: "<<mEffectCount;

				for(int i = 0; i < mEffectCount; i++)
				{
					getline(fileEM, lineData);

					getline(fileEM, lineData);
					sscanf_s(lineData.data(), "ID %d", &mListEffect[i].id);
					cout<<"\nID "<<mListEffect[i].id;

					getline(fileEM, lineData);
					const char* effectName = lineData.c_str();
					effectName += 5;

					if(strcmp(effectName, "BW") == 0)
					{
						mListEffect[i].effectName = Screen;
					}
					else
					{
						if(strcmp(effectName, "Blur") == 0)
						{
							mListEffect[i].effectName = Blur;
						}
						else
						{
							if(strcmp(effectName, "Bloom") == 0)
							{
								mListEffect[i].effectName = Bloom;
							}
							else
							{
								if(strcmp(effectName, "DepthOfField") == 0)
								{
									mListEffect[i].effectName = DepthOfField;
								}
								else
								{
									if(strcmp(effectName, "Gray") == 0)
									{
										mListEffect[i].effectName = Gray;
									}
								}
							}
						}
					}

					getline(fileEM, lineData);
					sscanf_s(lineData.data(), "NoPasses: %d", &mListEffect[i].passCount);
					mListEffect[i].CreateListPass(mListEffect[i].passCount);
					cout<<"\nNoPasses: "<< mListEffect[i].passCount;

					for(int j = 0; j < mListEffect[i].passCount; j++)
					{
						getline(fileEM, lineData);
						sscanf_s(lineData.data(), "PassID %d", &mListEffect[i].mListPass[j].id);
						cout<<"\nPassID: "<<mListEffect[i].mListPass[j].id;

						getline(fileEM, lineData);
						const char* passName = lineData.c_str();
						passName += 9;

						if(strcmp(passName, "BW") == 0)
						{
							mListEffect[i].mListPass[j].passName = BW;
						}
						else
						{
							if(strcmp(passName, "Blur") == 0)
							{
								mListEffect[i].mListPass[j].passName = BLUR;
							}
							else
							{
								if(strcmp(passName, "Prebloom") == 0)
								{
									mListEffect[i].mListPass[j].passName = PREBLOOM;
								}
								else
								{
									if(strcmp(passName, "PostBloom") == 0)
									{
										mListEffect[i].mListPass[j].passName = POSTBLOOM;
									}
									else
									{
										if(strcmp(passName, "DepthOfField") == 0)
										{
											mListEffect[i].mListPass[j].passName = DEPTH_OF_FIELD;
										}
										else
										{
											if(strcmp(passName, "Gray") == 0)
											{
												mListEffect[i].mListPass[j].passName = GRAY;
											}
										}
									}
								}
							}
						}
						cout<<"\nPassName: "<< mListEffect[i].mListPass[j].passName;

						int shaderId;
						getline(fileEM, lineData);
						sscanf_s(lineData.data(), "   ShaderID %d", &shaderId);
						cout<<"\n   Shader "<<shaderId;
						mListEffect[i].mListPass[j].shader = &mListShader[shaderId];

						getline(fileEM, lineData);
						const char* texInfo = lineData.c_str();
						texInfo += 13;

						//Read Texture  Textures: 1c, 0, 0
						mListEffect[i].mListPass[j].CreateTexsource(mFboCount);

						int count = 0;
						while((texInfo != "") && (count < mFboCount))
						{
							int fboId = texInfo[0] - 0x30;
							texInfo += 1;
							if(texInfo != "")
							{
								switch(texInfo[0])
								{
								case 'c':
									mListEffect[i].mListPass[j].texSource[count].texType = COLOR_TEXTURE;
									mListEffect[i].mListPass[j].texSource[count].fbo = &mListFbo[fboId - 1];
									if(count < mFboCount - 1)
									{
										texInfo += 3;
									}
									else
									{
										texInfo += 1;
									}
									break;
								case 'd':
									mListEffect[i].mListPass[j].texSource[count].texType = DEPTH_TEXTURE;
									mListEffect[i].mListPass[j].texSource[count].fbo = &mListFbo[fboId - 1];
									if(count < mFboCount - 1)
									{
										texInfo += 3;
									}
									else
									{
										texInfo += 1;
									}
									break;
								case ',':
									mListEffect[i].mListPass[j].texSource[count].texType = NON_TEXTURE;
									mListEffect[i].mListPass[j].texSource[count].fbo = 0;
									if(count < mFboCount - 1)
									{
										texInfo += 2;
									}
									else
									{
										texInfo += 1;
									}
									break;
								default:
									mListEffect[i].mListPass[j].texSource[count].texType = NON_TEXTURE;
									mListEffect[i].mListPass[j].texSource[count].fbo = 0;
									break;
								}				
							}
							else
							{
								mListEffect[i].mListPass[j].texSource[count].texType = NON_TEXTURE;
								mListEffect[i].mListPass[j].texSource[count].fbo = 0;
							}
							count ++;
						}

						getline(fileEM, lineData);
						sscanf_s(lineData.data(), "   Target: %d", &mListEffect[i].mListPass[j].targetFboId);
						//mListEffect[i].mListPass[j].targetFbo = &mListFbo[mListEffect[i].mListPass[j].targetFboId];
						cout<<"\n   Target: "<< mListEffect[i].mListPass[j].targetFboId;

						getline(fileEM, lineData);
						
						if(mListEffect[i].mListPass[j].passName == DEPTH_OF_FIELD)
						{
							mListEffect[i].mListPass[j].CreateListData(MAX_OTHER_DATA);
							sscanf_s(lineData.data(), "   OtherData: %f, %f, %f, %f, %f", &mListEffect[i].mListPass[j].otherData[0], &mListEffect[i].mListPass[j].otherData[1], &mListEffect[i].mListPass[j].otherData[2], &mListEffect[i].mListPass[j].otherData[3], &mListEffect[i].mListPass[j].otherData[4]);
						}
						else
						{
							mListEffect[i].mListPass[j].CreateListData(1);
							sscanf_s(lineData.data(), "   OtherData: %f", &mListEffect[i].mListPass[j].otherData[0]);							
						}

						mListEffect[i].mListPass[j].model = mModel;
					}
				}
			}
		}
	}
	else
	{
		cout<<"\n File EM.txt is not found \n";
	}
}
	
void EffectManager::Render(int effectId)
{
	for(int i = 0; i < mListEffect[effectId].passCount; i++)
	{
		if(mListEffect[effectId].mListPass[i].targetFboId > 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, mListFbo[mListEffect[effectId].mListPass[i].targetFboId - 1].fboId);
		}
		mListEffect[effectId].mListPass[i].Render();

	}
	
}

void EffectManager::Update()
{
	InputManager *input = InputManager::GetInstance();
	if(input->is_KeyPressed)
	{
		switch(input->keyCode)
		{
		case KEY_SCREEN:
			if(Screen < mEffectCount)
			{
				mCurrentEffect = Screen;
			}			
			break;
		case KEY_BLUR:
			if(Screen < mEffectCount)
			{
				mCurrentEffect = Blur;
			}
			break;
		case KEY_BLOOM:
			if(Screen < mEffectCount)
			{
				mCurrentEffect = Bloom;
			}
			break;
		case KEY_DOF:
			if(Screen < mEffectCount)
			{
				mCurrentEffect = DepthOfField;
			}
			break;
		case KEY_GRAY:
			if(Screen < mEffectCount)
			{
				mCurrentEffect = Gray;
			}
			break;
		}
	}
}

EffectManager::~EffectManager(void)
{
	if(	mListShader != 0)
	{
		delete[] mListShader;
		mListShader = 0;
	}

	if(	mListFbo != 0)
	{
		delete[] mListFbo;
		mListFbo = 0;
	}

	if(mModel != 0)
	{
		delete mModel;
		mModel = 0;
	}

	if(mListEffect != 0)
	{
		delete[] mListEffect;
		mListEffect = 0;
	}
}
