#include "StdAfx.h"
#include "Object.h"

extern float delTime;
extern Camera *sceneCamera;
float angle = 0.01f;
int numindice, numvertex;
extern float uTime;
Object::Object(void)
{
	texCubeCount = 0;
}

void Object::Init()
{
	// Set vector
	mScale = Vector3(1.0f, 1.0f, 1.0f);
	mRotate = Vector3(0.0f, 0.0f, 0.0f);
	mPosition = Vector3(0.0f, 0.0f, -5.5f);
}

void Object::SetScale(Vector3 scale)
{
	mScale = Vector3(scale);
}

void Object::SetRotation(Vector3 rotate)
{
	mRotate = Vector3(rotate);
}

void Object::SetTranlation(Vector3 translate)
{
	mPosition = Vector3(translate);
}

Matrix Object::CalculateWorldMatrix()
{
	Matrix worldMatrix;
	Matrix tranMatrix, scaleMatrix, rotateMatrix, rotXMatrix, rotYMatrix, rotZMatrix;

	scaleMatrix.SetScale(mScale);
	tranMatrix.SetTranslation(mPosition);
	rotXMatrix.SetRotationX(mRotate.x);
	rotYMatrix.SetRotationY(mRotate.y);
	rotZMatrix.SetRotationZ(mRotate.z);
	rotateMatrix = rotZMatrix * rotXMatrix * rotYMatrix;
	worldMatrix = scaleMatrix * rotateMatrix * tranMatrix;
	return worldMatrix;
}

void Object::Render()
{
	glUseProgram(mShaders->program);

	SendAttribute();
	SendLight();
	SendTexture();

	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawElements(GL_TRIANGLES, mModel->GetNumIndice(), GL_UNSIGNED_INT, 0);

	SendRest();

}

void Object::SendAttribute()
{
	for(int i = 0; i < mShaders->numState; i++)
	{
		glEnable(mShaders->nState[i]);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	glBindBuffer(GL_ARRAY_BUFFER, mModel->GetVboil());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mModel->GetIboil());

	Matrix wvpMatrix = CalculateWorldMatrix() * sceneCamera->mView * sceneCamera->mProject;

	// Send Attribute and uniform
	if(mShaders->a_locPosition != -1)
	{
		glEnableVertexAttribArray(mShaders->a_locPosition);
		glVertexAttribPointer(mShaders->a_locPosition, sizeof(Vector3)/sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, pos));
	}

	if(mShaders->a_locTextcoord != -1)
	{
		glEnableVertexAttribArray(mShaders->a_locTextcoord);
		glVertexAttribPointer(mShaders->a_locTextcoord, sizeof(Vector2)/sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, textcoord));
	}

	if(mShaders->u_locWVP != -1)
	{
		glUniformMatrix4fv(mShaders->u_locWVP, 1, GL_FALSE, (GLfloat*) wvpMatrix.m);
	}

	// Fog effect
	if(mShaders->u_locWorldW != -1)
	{
		glUniformMatrix4fv(mShaders->u_locWorldW, 1, GL_FALSE, (GLfloat*) CalculateWorldMatrix().m);
	}

	if(mShaders->u_locPosCameraW != -1)
	{
		glUniform3f(mShaders->u_locPosCameraW, sceneCamera->mPosition.x, sceneCamera->mPosition.y,sceneCamera->mPosition.z);
	}

	if(mShaders->u_locFogStart != - 1)
	{
		glUniform1f(mShaders->u_locFogStart, sceneCamera->fogStart);
	}

	if(mShaders->u_locFogLength != - 1)
	{
		glUniform1f(mShaders->u_locFogLength, sceneCamera->fogLength);
	}

	if(mShaders->u_locTime != -1)
	{
		
		glUniform1f(mShaders->u_locTime, uTime);
	}

	//Normal mapping
	if(mShaders->a_Normal != -1)
	{
		glEnableVertexAttribArray(mShaders->a_Normal);
		glVertexAttribPointer(mShaders->a_Normal, sizeof(Vector3)/sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	}

	if(mShaders->a_Bitagent != -1)
	{
		glEnableVertexAttribArray(mShaders->a_Bitagent);
		glVertexAttribPointer(mShaders->a_Bitagent, sizeof(Vector3)/sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, bitangent));
	}

	if(mShaders->a_Tagent != -1)
	{
		glEnableVertexAttribArray(mShaders->a_Tagent);
		glVertexAttribPointer(mShaders->a_Tagent, sizeof(Vector3)/sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
	}
}

void Object::SendLight()
{

	for(int i = 0; i < lightCount; i++)
	{
		if(mShaders->u_locLightPos[i] != -1)
		{
			glUniform3f(mShaders->u_locLightPos[i], Light::GetInstance()->mListLight[i].mPosition.x, Light::GetInstance()->mListLight[i].mPosition.y, Light::GetInstance()->mListLight[i].mPosition.z );
		}

		if(mShaders->u_locLightDiffuse[i] != -1)
		{
			glUniform3f(mShaders->u_locLightDiffuse[i], Light::GetInstance()->mListLight[i].mDiffuseColor.x, Light::GetInstance()->mListLight[i].mDiffuseColor.y, Light::GetInstance()->mListLight[i].mDiffuseColor.z);
		}

		if(mShaders->u_locLightSpecular[i] != -1)
		{
			glUniform3f(mShaders->u_locLightSpecular[i], Light::GetInstance()->mListLight[i].mSpecularColor.x, Light::GetInstance()->mListLight[i].mSpecularColor.y, Light::GetInstance()->mListLight[i].mSpecularColor.z);
		}
		
		if(mShaders->u_locSpecPower[i] != -1)
		{
			glUniform1f(mShaders->u_locSpecPower[i],  Light::GetInstance()->mListLight[i].specPower);
		}

	}

	if(mShaders->u_locAmbient != -1)
	{
		glUniform3f(mShaders->u_locAmbient, Light::GetInstance()->mAmbientColor.x, Light::GetInstance()->mAmbientColor.y, Light::GetInstance()->mAmbientColor.z);
	}

	if(mShaders->u_locLightWeight != -1)
	{
		glUniform1f(mShaders->u_locLightWeight, Light::GetInstance()->mAmbientWeight);
	}

}

void Object::SendTexture()
{
	int texUnit = 0;
	// Uniform texture 2D
	for(int i = 0; i < tex2DCount; i++)
	{
		if(mShaders->u_texture2D[i] != -1)
		{
			glActiveTexture(GL_TEXTURE0 + texUnit);
			glBindTexture(GL_TEXTURE_2D, mTexture[i]->textureID);
			glUniform1i(mShaders->u_texture2D[i],texUnit);
			texUnit++;
		}
	}

	// Uniform texture Cube
	for(int i = 0; i < texCubeCount; i++)
	{
		if(mShaders->u_textureCube[i] != -1)
		{
			glActiveTexture(GL_TEXTURE0 + texUnit);
			glBindTexture(GL_TEXTURE_CUBE_MAP, mCube[i]->textureID);
			glUniform1i(mShaders->u_textureCube[i],texUnit);
			texUnit++;
		}
	}
}

void Object::SendRest()
{
	for(int i = 0; i < mShaders->numState; i++)
	{
		glDisable(mShaders->nState[i]);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_TEXTURE_CUBE_MAP, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::Update( float deltaTime )
{	
}
Object::~Object(void)
{
}
