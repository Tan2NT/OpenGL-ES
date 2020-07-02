#pragma once
#include "stdafx.h"
#include <vector>
#include "GameObject.h"
#include "Singleton.h"
#include "Camera.h"

class SceneManager : public SingletonTemplate<SceneManager>
{
	Camera*		m_camera;
	unsigned int m_ObjectsCount;
	std::vector<GameObject> m_Objects;
public:
	SceneManager();
	~SceneManager();
	void	Init(char* path);
	void	Update(float deltaTime);
	void	Draw(ESContext *esContext);
	void	HandleInput(unsigned char keyCode);
	Camera* GetCamera() { return m_camera; }
};

inline SceneManager* GetSceneManager()
{
	return SceneManager::GetInstance();
}

