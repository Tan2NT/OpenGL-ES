#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"

class Texture
{
private:
	int		m_target;
	GLenum	m_tilingMode;
public:
	int		m_Id;
	GLuint	m_textureHandle;	
	void	Init2DTexture(char* path);
	void	InitCubeTexture(char* path);
	int		GetTarget() { return m_target; };
	void	SetTiling(GLuint tiling)	{ m_tilingMode = tiling; }

	Texture();
	~Texture();
};

