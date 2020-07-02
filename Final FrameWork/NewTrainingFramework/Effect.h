#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Globals.h"
#include "Pass.h"

enum effectName{
	Screen,
	Blur,
	Bloom,
	DepthOfField,
	Gray
};

class Effect
{
public:
	Effect(void);
	int id;
	int effectName;
	int passCount;
	Pass *mListPass;

	void CreateListPass(int numberPass);
	void Render();
	~Effect(void);
};
