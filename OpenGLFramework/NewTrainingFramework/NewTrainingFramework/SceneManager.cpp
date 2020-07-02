#include "stdafx.h"
#include "SceneManager.h"
#include "ResourcesManager.h"

extern bool				g_isKeyPress;
extern unsigned char	g_keyCode;

SceneManager::SceneManager()
{
	m_ObjectsCount = 0;
	m_camera = NULL;
}


SceneManager::~SceneManager()
{
	if (m_camera != NULL)
	{
		delete m_camera;
		m_camera = NULL;
	}
}

void SceneManager::Init(char* path)
{
	FILE *f = fopen(path, "r");

	if (f == NULL)
	{
		esLogMessage("Can't open %s file", path);
		return;
	}

	int temp;
	fscanf(f, "#Objects\n");
	fscanf(f, "ObjectsCount %d\n", &m_ObjectsCount);
	for (int i = 0; i < m_ObjectsCount; i++)
	{
		int id;
		GameObject object;
		fscanf(f, "ID %d\n", &object);
		fscanf(f, "MODEL %d\n", &id);
		object.SetModel(GetResourcesManager()->GetModelById(id));
		
		Texture** textures;
		int numTexs = -1;
		fscanf(f, "2DTEXTURES %d\n", &numTexs);

		if (numTexs > 0)
		{
			//2d Textures
			textures = new Texture*[numTexs];
			for (int i = 0; i < numTexs; i++)
			{
				fscanf(f, "TEXTURE %d\n", &id);
				textures[i] = GetResourcesManager()->Get2DTextureById(id);
			}			
			object.SetTextures(textures, numTexs);
			fscanf(f, "CUBETEXTURES %d\n", &numTexs);
		}
		else
		{
			//Cube texture

			fscanf(f, "CUBETEXTURES %d\n", &numTexs);
			textures = new Texture*[numTexs];
			for (int i = 0; i < numTexs; i++)
			{
				fscanf(f, "CUBETEXTURE %d\n", &id);
				textures[i] = GetResourcesManager()->GetCubeTextureById(id);
			}

			object.SetTextures(textures, numTexs);
		}

		fscanf(f, "SHADER %d\n", &temp);
		object.SetShader(GetResourcesManager()->GetShaderById(temp));

		float x, y, z;
		fscanf(f, "POS %f, %f, %f\n", &x, &y, &z);
		object.SetTranslate(Vector3(x, y, z));
		fscanf(f, "ROTATE %f, %f, %f\n", &x, &y, &z);
		object.SetRotate(Vector3(x, y, z));
		fscanf(f, "SCALE %f, %f, %f\n", &x, &y, &z);
		object.SetScale(Vector3(x, y, z));

		m_Objects.push_back(object);
		fscanf(f, "\n");
	}

	fscanf(f, "\n");
	fscanf(f, "#CAMERA\n");
	float near_, far_, fov_, moveSpeed, rotSpeed, aspect;
	fscanf(f, "NEAR %f\n", &near_);
	fscanf(f, "FAR %f\n", &far_);
	fscanf(f, "FOV %f\n", &fov_);
	fscanf(f, "MOVE_SPEED %f\n", &moveSpeed);
	fscanf(f, "ROT_SPEED %f\n", &rotSpeed);
	aspect = Globals::screenWidth / Globals::screenHeight;
	
	m_camera = new Camera();
	m_camera->Init(fov_, aspect, near_, far_, moveSpeed, rotSpeed);
}

void SceneManager::Update(float deltaTime)
{
	if (g_isKeyPress)
	{
		m_camera->HandleKeyInput(g_keyCode, deltaTime);

		/*for (std::vector<GameObject>::iterator it = m_Objects.begin(); it != m_Objects.end(); it++)
		{
			it->HandleInput(g_keyCode, deltaTime);
		}*/
		m_Objects[0].HandleInput(g_keyCode, deltaTime);
		g_isKeyPress = false;
	}

	for (std::vector<GameObject>::iterator it = m_Objects.begin(); it != m_Objects.end(); it++)
	{
		it->Update(deltaTime);
	}
}

void SceneManager::Draw(ESContext *esContext)
{
	for (std::vector<GameObject>::iterator it = m_Objects.begin(); it != m_Objects.end(); it++)
	{
		it->Draw(esContext);
	}
}

void SceneManager::HandleInput(unsigned char keyCode)
{
}
