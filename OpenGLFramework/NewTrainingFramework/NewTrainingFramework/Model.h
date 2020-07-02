#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"

class Model
{
private:
	int		m_modelId;
	GLuint	m_vboId, m_iboId;
	GLuint	m_numOfVertices, m_numOfIndices;
public:
	
	void	SetModelId(int id) { m_modelId = id; };
	int		GetModelId() { return m_modelId; }
	GLuint	GetVboId() { return m_vboId; }
	GLuint	GetIboId() { return m_iboId; }
	int		GetNumberOfVertices() { return m_numOfVertices; }
	int		GetNumberOfIndices() { return m_numOfIndices; }

	Model();
	void	Init(char* path);

	~Model();
};

