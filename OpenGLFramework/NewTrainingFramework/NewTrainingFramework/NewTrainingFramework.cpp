// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "Model.h"
#include "Texture.h"
#include "GameObject.h"
#include "ResourcesManager.h"
#include "SceneManager.h"
#include "../Utilities/TGA.h"
#include <time.h>
#include <chrono>
#include <vector>
#include <iostream>

using namespace std;

GLuint vboId;
GLuint iboId;

std::vector<GameObject> m_Objects;
Shaders *shader = new Shaders();

bool			g_isKeyPress;
unsigned char	g_keyCode;

int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	GetResourcesManager()->Init("RM.txt");

	GetSceneManager()->Init("SM.txt");

	return 0;
}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//auto start = chrono::steady_clock::now();
	clock_t start, end;
	start = clock();

	//  Insert the code that will be timed
	//auto end = chrono::steady_clock::now();

	GetSceneManager()->Draw(esContext);

	end = clock();
	//printf("start %d", start);
	int cpuTime = (end - start);
	//cout<<"\n Start:" << start << "  - end: "<<end<<"  estime: " << cpuTime;

	// Store the time difference between start and end
	//auto diff = end - start;
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update ( ESContext *esContext, float deltaTime )
{
	GetSceneManager()->Update(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	g_isKeyPress = bIsPressed;
	g_keyCode = key;

	if (bIsPressed)
	{
		GetSceneManager()->HandleInput(key);
	}
}

void CleanUp()
{
}

//////////////////////////////////////////// WINDOWS main function ////////////////////////////////////////////////////
#ifdef _WIN32

#include <conio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	printf("Press any key...\n");
	_getch();

	return 0;
}

#endif
//////////////////////////////////////////// WINDOWS main function ////////////////////////////////////////////////////
