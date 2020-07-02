#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" 
#define MAX_TEXTURE 5
class Texture
{
public:
	int id;
	GLuint textureID;
	int texturesCount;
	GLenum target;
	Texture(void);
	void Init(const char* textureFilePath, unsigned int TILING);
	~Texture(void);
};
