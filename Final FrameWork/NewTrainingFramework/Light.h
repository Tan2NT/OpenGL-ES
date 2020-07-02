#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Globals.h"
#include "Singleton.h"
#include "Math.h"
enum Move{
	CIRCLE,
	DIRECTION
};

struct LightInfo
{
	int id;
	Vector3 mPosition, mDiffuseColor, mSpecularColor;
	float radius, speed;
	char type[10];
	int move;
	int direction;
	float specPower;
};

class Light:public Singleton<Light>
{
public:

	int mLightsCount;
	Vector3 mAmbientColor;
	float mAmbientWeight;
	LightInfo* mListLight;

	void UpdatePosition(float deltatime);
	void Init(int numLight);
	void InitLight(int index, Vector3 lightPos, Vector3 diffuseColor, Vector3 specularColor, float specularPower, const char* lightType , const char* lightMoving, float lightRadius, float lightSpeed);
	LightInfo* GetLight(int lightId);
	Light(void);
	~Light(void);	
};
