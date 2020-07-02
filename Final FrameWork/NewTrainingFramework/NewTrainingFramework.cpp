// NewTrainingFramework.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include "Object.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Light.h"
#include "InputManager.h"
#include "EffectManager.h"

GLuint vboId, vIndice;
Shaders myShaders;

SceneManager* resSM;
Camera* sceneCamera;
ResoureManager* resRM;
Light *mLight;
float delTime;
float uTime = 0.0f;
int Init ( ESContext *esContext )
{
	sceneCamera = new Camera();
	sceneCamera->Init();
	mLight = new Light();

	EffectManager::GetInstance()->Init("../Resources/Managers/EM.txt");
	ResoureManager::GetInstance()->Init("../Resources/Managers/RM.txt");
	SceneManager::GetInstance()->Init("../Resources/Managers/SM.txt");
	return myShaders.Init("../Resources/Shaders/VSEffect.glsl", "../Resources/Shaders/FSBW.glsl");
}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT);
	SceneManager::GetInstance()->Render();
	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface);
}

void Update ( ESContext *esContext, float deltaTime )
{
	sceneCamera->Update(deltaTime);
	SceneManager::GetInstance()->Update(deltaTime);
	Light::GetInstance()->UpdatePosition(deltaTime);
	delTime = deltaTime;
	uTime += 0.8f * delTime;

}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	InputManager::GetInstance()->IsKeyPressed(key, bIsPressed);
}

void CleanUp()
{
	delete sceneCamera;	
	Light::FreeInstance();
	SceneManager::FreeInstance();
	ResoureManager::FreeInstance();
	InputManager::FreeInstance();
	EffectManager::FreeInstance();
}

int _tmain(int argc, _TCHAR* argv[])
{
	ESContext esContext;

	esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello MR.Tan", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

