#include "StdAfx.h"
#include "NewDraw.h"

int numindice, numvertex;
NewDraw::NewDraw(void)
{
	myCamera = new Camera();
	gCamera = new GCamera();
	gModel = new Model();
	gTexture = new Texture();
}

int NewDraw::Init(ESContext *esContext)
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
	gModel->Init("../Resources/Model/Woman1.nfg");
	gTexture->Init("../Resources/Textures/Woman1.tga", GL_REPEAT);
	TexID = gTexture->TextureID;
	
	modelID = gModel->GetVboil();
	indiceID = gModel->GetIboil();
	numberOfIndice = gModel->GetNumIndice();
	cout<<"\n"<<"num of Indices : "<<gModel->GetNumIndice();

	// Set vector
	v_sale = Vector3(1.0f, 1.0f, 1.0f);
	v_rotate = Vector3(0.0f, 0.0f, 0.0f);
	v_translate = Vector3(0.0f, 0.0f, -0.5f);

	//Init matrix
	m_rotx.SetRotationX(v_rotate.x);
	m_roty.SetRotationY(v_rotate.y);
	m_rotz.SetRotationZ(v_rotate.z);
	m_rotate = m_rotz * m_rotx * m_roty;

	m_scale.SetScale(v_sale);
	m_tran.SetTranslation(v_translate);

	m_view.SetIdentity();
	m_project.SetPerspective(45.0f, 1.0f, 0.1f, 1000.0f) ;

	m_mvp = m_world * m_view * m_project;
	//m_project.SetIdentity();

	//creation of shaders and program 
	return myShaders1.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
}

void NewDraw::SetScale(Vector3 scale)
{
	v_sale = Vector3(scale);
}

void NewDraw::SetRotation(Vector3 rotate)
{
	v_rotate = Vector3(rotate);
}

void NewDraw::SetTranlation(Vector3 translate)
{
	v_translate = Vector3(translate);
}

void NewDraw::Render(ESContext *esContext)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(myShaders1.program);
	glEnable(GL_DEPTH_TEST);

	glBindBuffer(GL_ARRAY_BUFFER, modelID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TexID);

	if(myShaders1.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders1.positionAttribute);
		glVertexAttribPointer(myShaders1.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if(myShaders1.colorAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders1.colorAttribute);
		glVertexAttribPointer(myShaders1.colorAttribute, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
	}
	
	if(myShaders1.textcoordAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders1.textcoordAttribute);
		glVertexAttribPointer(myShaders1.textcoordAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)28);
	}

	if(myShaders1.mvp_Attribute != -1)
	{
		glUniformMatrix4fv(myShaders1.mvp_Attribute, 1, GL_FALSE, (GLfloat*) m_mvp.m);
	}

	if(myShaders1.textureUniform != -1)
	{
		glUniform1i(myShaders1.textureUniform, 0);
	}
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawElements(GL_TRIANGLES, numberOfIndice, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface);
}

void NewDraw::Key( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	//gCamera->Key(key, bIsPressed);
	myCamera->Key(key, bIsPressed);
}

void NewDraw::Update( ESContext *esContext, float deltaTime )
{
	//gCamera->Update(deltaTime);
	myCamera->update(deltaTime);
	m_scale.SetScale(v_sale);
	m_tran.SetTranslation(v_translate);
	m_rotx.SetRotationX(v_rotate.x);
	m_roty.SetRotationY(v_rotate.y);
	m_rotz.SetRotationZ(v_rotate.z);
	m_rotate = m_rotz * m_rotx * m_roty;
	m_world = m_scale * m_rotate * m_tran;

	m_mvp = m_world * myCamera->cameraMatrix * m_project;
}
NewDraw::~NewDraw(void)
{
	delete gCamera;
	delete myCamera;
	delete gModel;
	delete gTexture;
}
