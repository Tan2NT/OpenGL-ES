#include "StdAfx.h"
#include "Effect.h"

Effect::Effect(void)
{
	mListPass = 0;
}

void Effect::CreateListPass(int numberPass)
{
	mListPass = new Pass[numberPass];
}

void Effect::Render()
{
	
}

Effect::~Effect(void)
{
	if(mListPass != 0)
	{
		delete[] mListPass;
		mListPass = 0;
	}
}
