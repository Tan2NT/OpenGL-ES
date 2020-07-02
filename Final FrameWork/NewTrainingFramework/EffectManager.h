#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Globals.h"
#include "Shaders.h"
#include "Singleton.h"
#include "FrameBufferObject.h"
#include "Math.h"
#include "Model.h"
#include "InputManager.h"
#include "Effect.h"

#define MAX_EFFECT_SHADER	7
#define MAX_FBO				3



class EffectManager :public Singleton<EffectManager>
{
private:
public:
	EffectManager(void);
	int mFboCount, mShaderCount, mEffectCount;
	int mCurrentEffect;
	Shaders *mListShader;
	FrameBufferObject *mListFbo;
	Effect *mListEffect;
	Model *mModel;

	void Init(const char *filePath);
	void Render(int EffectId);
	void Update();

	~EffectManager(void);
};
