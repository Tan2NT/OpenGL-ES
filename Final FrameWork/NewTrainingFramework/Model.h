#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"

class Model
{
public:
	GLuint vBoid, iBoid;
	Vertex* vertexData;
	int* indiceData;
	int id;
	GLsizei numIndice;
	Model(void);
	void Init(const char* filePath);
	GLuint GetVboil();
	GLuint GetIboil();
	GLsizei GetNumIndice();
	~Model(void);
};