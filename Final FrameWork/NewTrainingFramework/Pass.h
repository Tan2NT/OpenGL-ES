#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Globals.h"
#include "Model.h"
#include "FrameBufferObject.h"
#define	MAX_OTHER_DATA	5

struct TextureInfo{
	FrameBufferObject *fbo;
	int texType;
	~TextureInfo()
	{
	}
};

enum TextureChoose{ 
	NON_TEXTURE,
	COLOR_TEXTURE,
	DEPTH_TEXTURE
};

enum PassName{
	BW,
	BLUR,
	PREBLOOM,
	POSTBLOOM,
	DEPTH_OF_FIELD,
	GRAY
};

class Pass
{
public:
	Pass(void);

	int passName;
	int id;
	int targetFboId;
	int textureCount;
	Model *model;

	Shaders *shader;
	TextureInfo* texSource;
	float *otherData;

	void CreateListData(int numberData);
	void CreateTexsource(int numberTex);
	void Render();
	void SendAttribute();
	void SendTexture();
	void SendData();
	void SendRest();
	~Pass(void);
};
