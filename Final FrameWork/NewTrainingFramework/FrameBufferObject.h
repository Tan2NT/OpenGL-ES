#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" 
#include "Globals.h"

class FrameBufferObject
{
public:
	GLuint fboId, colorTexId, depthTexId;
	GLint width, height;
	FrameBufferObject(void);
	~FrameBufferObject(void);
	void Init();
};
