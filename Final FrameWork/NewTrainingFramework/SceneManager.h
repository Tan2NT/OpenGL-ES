#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Globals.h"
#include <conio.h>
#include "Object.h"
#include "Camera.h"
#include "Singleton.h"
#include "FrameBufferObject.h"
#include "Math.h"
#include "EffectManager.h"
#include "FontGame.h"
#define MAX_SHADER 5

class SceneManager : public Singleton<SceneManager>
{
public:
	int objectCount;
	Object* listObject;
	void Init(const char* filePath);
	void Render();
	void Update(float deltaTime);
	FontGame *fontArialMS;

	SceneManager(void);
	~SceneManager(void);
};
