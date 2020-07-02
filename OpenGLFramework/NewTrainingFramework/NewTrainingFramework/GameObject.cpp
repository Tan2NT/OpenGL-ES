#include "stdafx.h"
#include "GameObject.h"
#include "SceneManager.h"

float angle = 1.0f;

GameObject::GameObject()
{
	m_objectId = 0;
	m_scale = Vector3(1.0f, 1.0f, 1.0f);
	m_rotate = Vector3(0.0f, 0.0f, 0.0f);
	m_translate = Vector3(0.0f, 0.0f, 0.0f);
	m_moveSpeed = 2.0f;
	m_textures = NULL;
	m_model = NULL;
	m_shader = NULL;
}


GameObject::~GameObject()
{
}

void GameObject::Init(Model *model, Texture **textures, int numTexs, Shaders *shader)
{
	SetModel(model);
	SetTextures(textures, numTexs);
	SetShader(shader);
}

void GameObject::SetModel(Model *model)
{
	m_model = model;
}

void GameObject::SetTextures(Texture **texture, int numTexs)
{
	m_textures = texture;
	m_numOfTextures = numTexs;
}

void GameObject::SetShader(Shaders *shader)
{
	m_shader = shader;
}

void GameObject::Update(float deltaTime)
{
}

Matrix GameObject::CalculateWorldMatrix()
{
	Matrix translateMatrix, scaleMatrix, rotateMatrix, rotateZMatrix, rotateXMatrix, rotateYMatrix;
	translateMatrix.SetTranslation(m_translate);
	scaleMatrix.SetScale(m_scale);
	rotateZMatrix.SetRotationZ(m_rotate.z);
	rotateXMatrix.SetRotationX(m_rotate.x);
	rotateYMatrix.SetRotationY(m_rotate.y);
	rotateMatrix = rotateZMatrix * rotateXMatrix * rotateYMatrix;
	Matrix worldMatrix = scaleMatrix * rotateMatrix * translateMatrix;
	return worldMatrix;
}

Matrix GameObject::CalculateMVPMatrix()
{
	//Caluculate World Matrix	
	Matrix mvpMatrix = CalculateWorldMatrix() * GetSceneManager()->GetCamera()->GetViewMatrix() * GetSceneManager()->GetCamera()->GetProjectionMatrix();

	return mvpMatrix;
}

void GameObject::Draw(ESContext *esContext)
{
	glUseProgram(m_shader->GetProgram());
	m_shader->EnableState();

	glBindBuffer(GL_ARRAY_BUFFER, m_model->GetVboId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->GetIboId());

	if (m_shader->u_mvpMatrix != -1)
	{
		Matrix mvpMatrix = CalculateMVPMatrix();
		glUniformMatrix4fv(m_shader->u_mvpMatrix, 1, GL_FALSE, (GLfloat*)&mvpMatrix);
	}

	if (m_shader->a_posL != -1)
	{
		glEnableVertexAttribArray(m_shader->a_posL);
		glVertexAttribPointer(m_shader->a_posL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (m_shader->a_uv != -1)
	{
		glEnableVertexAttribArray(m_shader->a_uv);
		glVertexAttribPointer(m_shader->a_uv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);
	}

	int activeTexIdx = 0;
	for (int i = 0; i < m_numOfTextures; i++)
	{
		if (m_shader->u_texsLocation[i] != -1)
		{
			if (m_textures[i]->GetTarget() == GL_TEXTURE_2D)
			{
				glActiveTexture(GL_TEXTURE0 + activeTexIdx);
				glBindTexture(GL_TEXTURE_2D, m_textures[i]->m_textureHandle);
				glUniform1i(m_shader->u_texsLocation[i], activeTexIdx);
				activeTexIdx++;
			}

			if (m_textures[i]->GetTarget() == GL_TEXTURE_CUBE_MAP)
			{
				glActiveTexture(GL_TEXTURE0 + activeTexIdx);
				glBindTexture(GL_TEXTURE_CUBE_MAP, m_textures[i]->m_textureHandle);
				glUniform1i(m_shader->u_texsLocation[i], activeTexIdx);
				activeTexIdx++;
			}
		}
	}

	glDrawElements(GL_TRIANGLES, m_model->GetNumberOfIndices(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	m_shader->DisableState();

}

void GameObject::SetScale(Vector3 scale)
{
	m_scale = scale;
}

void GameObject::SetRotate(Vector3 rot)
{
	m_rotate = rot;
}

void GameObject::SetTranslate(Vector3 tran)
{
	m_translate = tran;
}

void GameObject::MoveLeft(float deltaTime)
{
	Vector4 moveL = Vector4(-deltaTime * m_moveSpeed, 0.0, 0.0, 1.0);
	Vector4 moveW = moveL * CalculateWorldMatrix();
	m_translate = Vector3(moveW.x, moveW.y, moveW.z);
}

void GameObject::MoveRight(float deltaTime)
{
	Vector4 moveL = Vector4(deltaTime * m_moveSpeed, 0.0, 0.0, 1.0);
	Vector4 moveW = moveL * CalculateWorldMatrix();
	m_translate = Vector3(moveW.x, moveW.y, moveW.z);
}

void GameObject::MoveForward(float deltaTime)
{
	Vector4 moveL = Vector4(0.0, 0.0, deltaTime * m_moveSpeed, 1.0);
	Vector4 moveW = moveL * CalculateWorldMatrix();
	m_translate = Vector3(moveW.x, moveW.y, moveW.z);
}

void GameObject::MoveBackward(float deltaTime)
{
	Vector4 moveL = Vector4(0.0, 0.0, -deltaTime * m_moveSpeed, 1.0);
	Vector4 moveW = moveL * CalculateWorldMatrix();
	m_translate = Vector3(moveW.x, moveW.y, moveW.z);
}

void GameObject::MoveUp(float deltaTime)
{
	Vector4 moveL = Vector4(0.0, deltaTime * m_moveSpeed, 0.0, 1.0);
	Vector4 moveW = moveL * CalculateWorldMatrix();
	m_translate = Vector3(moveW.x, moveW.y, moveW.z);
}

void GameObject::MoveDown(float deltaTime)
{
	Vector4 moveL = Vector4(0.0, -deltaTime * m_moveSpeed, 0.0, 1.0);
	Vector4 moveW = moveL * CalculateWorldMatrix();
	m_translate = Vector3(moveW.x, moveW.y, moveW.z);
}

void GameObject::HandleInput(unsigned char keyCode, float deltaTime)
{
		if (keyCode == 46)	//DELETE - MOVE LEFT
		{
						MoveLeft(deltaTime);
		}			
		if (keyCode == 34)	// PAGE_DOWN - MOVE RIGHT
		{
						MoveRight(deltaTime);
		}
		if (keyCode == 36)	// HOME - MOVE forward
		{
						MoveForward(deltaTime);
		}

		if (keyCode == 35)	// END - MOVE backward
		{
						MoveBackward(deltaTime);
		}
		if (keyCode == 45)	// INSERT - MOVE DOWN
		{
						MoveDown(deltaTime);
		}
		if (keyCode == 33)	// PAGE_UP - MOVE UP 
		{
						MoveUp(deltaTime);
		}
}