#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" 
#define MAX_CUBE_TEXTURE 3
class CubeTexture
{
public:
	int id;
	GLuint textureID;
	void Init(const char*, unsigned int TILING); 

	GLubyte* GetSubBuffer(char *buffer, int x, int y, int offsetX, int offsetY, int width, int height, int chanel);
	CubeTexture(void);
	~CubeTexture(void);
};
