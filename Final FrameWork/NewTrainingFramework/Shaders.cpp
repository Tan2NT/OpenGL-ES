#include <stdafx.h>
#include "Shaders.h"

Shaders::Shaders()
{
	nState = 0;
}

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	//finding location of uniforms / attributes
	a_locPosition = glGetAttribLocation(program, "a_posL");
	a_locColor = glGetAttribLocation(program, "a_coL");
	u_locWVP = glGetUniformLocation(program, "u_WVP");
	a_locTextcoord = glGetAttribLocation(program, "a_textcoordL");
	u_locWorldW = glGetUniformLocation(program, "u_worldW");
	u_locPosCameraW = glGetUniformLocation(program, "u_posCameraW");

	//Fog
	u_locFogStart = glGetUniformLocation(program, "u_fogStart");
	u_locFogLength = glGetUniformLocation(program, "u_fogLength");

	//Normal mapping
	a_Bitagent = glGetAttribLocation(program, "a_bitangentL");
	a_Normal = glGetAttribLocation(program, "a_normalL");
	a_Tagent = glGetAttribLocation(program, "a_tangentL");
	u_normalMap = glGetUniformLocation(program, "u_normalMap");
	u_objectTexture = glGetUniformLocation(program, "u_objectTexture");

	u_locLightWeight = glGetUniformLocation(program, "u_weight");
	
	//Blur a_pos, step;
	u_locStep = glGetUniformLocation(program, "u_step");

	u_locNear = glGetUniformLocation(program, "u_near");
	u_locFar = glGetUniformLocation(program, "u_far");
	u_locFade = glGetUniformLocation(program, "u_fade");
	u_locClarity = glGetUniformLocation(program, "u_clarity");



	//Bloom
	u_locLimit = glGetUniformLocation(program, "u_limit");
	u_BlurredCBuffer = glGetUniformLocation(program, "BlurredCBuffer");

	// Get uniform location of 2D textures
	for(int i = 0; i < MAX_TEXTURE_2D; i++)
	{
		char locTexture[30];
		sprintf_s(locTexture, "u_texture2D%d", i);
		u_texture2D[i] = glGetUniformLocation(program, locTexture);
	}

	// Get uniform location of Cube tectures
	for(int i = 0; i < MAX_TEXTURE_CUBE; i++)
	{
		char locTexture[30];
		sprintf_s(locTexture, "u_textureCube%d", i);
		u_textureCube[i] = glGetUniformLocation(program, locTexture);
		if ( u_textureCube[i] != -1)
		{
			
		}
	}

	u_locAmbient = glGetUniformLocation(program, "u_AmbientColor");
	// Get uniform location of Light Position
	for(int i = 0; i < MAX_LIGHT; i++)
	{
		char locLightDirection[30];
		sprintf_s(locLightDirection, "u_LightPos%d", i);
		u_locLightPos[i] = glGetUniformLocation(program, locLightDirection);
	}

	// Get uniform location Lights diffuse
	for(int i = 0; i < MAX_LIGHT; i++)
	{
		char locLightDiffuse[30];
		sprintf_s(locLightDiffuse, "u_LightDiffuse%d", i);
		u_locLightDiffuse[i] = glGetUniformLocation(program, locLightDiffuse);
	}

	// Get uniform location of Lights specular
	for(int i = 0; i < MAX_LIGHT; i++)
	{
		char locLightSpecular[30];
		sprintf_s(locLightSpecular, "u_LightSpecular%d", i);
		u_locLightSpecular[i] = glGetUniformLocation(program, locLightSpecular);
	}
	
	// Gwt uniform location of SpecPower
	for(int i = 0; i < MAX_LIGHT; i++)
	{
		char locSpecPower[30];
		sprintf_s(locSpecPower, "u_specPower%d", i);
		u_locSpecPower[i] = glGetUniformLocation(program, locSpecPower);
	}
	u_locTime = glGetUniformLocation(program, "u_Time");

	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	if(nState != 0)
	{
		delete [] nState;
	}
}