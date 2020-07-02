#include "StdAfx.h"
#include "Light.h"

Light::Light(void)
{
	mLightsCount = 0;
}

void Light::Init(int numLight)
{
	mListLight = new LightInfo[numLight];
}

void Light::InitLight(int index, Vector3 lightPos, Vector3 diffuseColor, Vector3 specularColor, float specularPower, const char* lightType , const char* lightMoving, float lightRadius, float lightSpeed)
{
	mListLight[index].mPosition = lightPos;
	mListLight[index].mDiffuseColor = diffuseColor;
	mListLight[index].mSpecularColor = specularColor;
	mListLight[index].specPower = specularPower;
	strcpy_s(mListLight[index].type, lightType);

	char moving[10];
	strcpy_s(moving, lightMoving);
	if(strcmp(moving, "CIRCLE") == 0)
	{
		mListLight[index].move = CIRCLE;
	}
	else 
	{
		mListLight[index].move = DIRECTION;
	}

	mListLight[index].radius = lightRadius;
	mListLight[index].speed = lightSpeed;
	mListLight[index].direction = 1;
}

void Light::UpdatePosition(float deltaTime)
{
	for(int i = 0; i < mLightsCount; i++)
	{
		if(mListLight[i].move == CIRCLE)
		{
			float angle = mListLight[i].radius * deltaTime;
			mListLight[i].mPosition.x = mListLight[i].mPosition.x * cos(angle) + mListLight[i].mPosition.z * sin(angle);
			mListLight[i].mPosition.z = mListLight[i].mPosition.z * cos(angle) - mListLight[i].mPosition.x * sin(angle);
		}
		else
		{
			if(mListLight[i].move == DIRECTION)
			{
				float deltaMove = mListLight[i].speed * deltaTime;
				if(	mListLight[i].mPosition.x >= 10.0f)
				{
					mListLight[i].direction = -1;
				}
				if(	mListLight[i].mPosition.x <= -10.0f)
				{
					mListLight[i].direction = 1;
				}
				mListLight[i].mPosition.x += deltaMove * mListLight[i].direction;
				
			}
		}
	}
}

LightInfo* Light::GetLight(int lightId)
{
	int i = 0;
	while(mListLight[i].id != lightId)
	{
		i++;
	}
	return &mListLight[i];
}

Light::~Light(void)
{
	if(mListLight != 0)
	{
		delete[] mListLight;
		mListLight = 0;
	}
}
