#pragma once
#include "../Utilities/utilities.h"
#include "stdio.h"
#define MAX_TEXTURE_2D 5
#define MAX_TEXTURE_CUBE 3
#define MAX_LIGHT 5

class Shaders 
{
private:
	
public:
	Shaders();
	int id;
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint a_locPosition, a_locColor, u_locWVP,  a_locTextcoord;
	GLint a_Normal, a_Bitagent, a_Tagent, u_mvp, u_world , u_normalMap, u_objectTexture;
	GLint u_locPosCameraW, u_locWorldW;

	GLint a_pos, u_locStep;
	GLint u_locLimit, u_ColorBuffer, u_BlurredCBuffer;
	GLint u_locFar, u_locFade, u_locClarity, u_locNear;

	GLint u_texture2D[MAX_TEXTURE_2D];
	GLint u_textureCube[MAX_TEXTURE_CUBE];
	GLint u_locSpecPower[MAX_LIGHT];
	GLint u_locLightPos[MAX_LIGHT], u_locLightSpecular[MAX_LIGHT], u_locLightDiffuse[MAX_LIGHT], u_locLightWeight, u_locAmbient;
	GLint u_locTime, u_locFogStart, u_locFogLength;

	int Init(char * fileVertexShader, char * fileFragmentShader);
	unsigned int *nState;
	int numState;
	~Shaders();
};