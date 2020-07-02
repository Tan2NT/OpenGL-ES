#include "StdAfx.h"
#include "Pass.h"

Pass::Pass(void)
{
	shader = 0;
	otherData = 0;
}

void Pass::CreateTexsource(int numberTex)
{
	texSource = new TextureInfo[numberTex];
}

void Pass::CreateListData(int numberData)
{
	otherData = new float[numberData];
}

void Pass::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	glUseProgram(shader->program);
	
	glBindBuffer(GL_ARRAY_BUFFER, model->vBoid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->iBoid);

	SendAttribute();
	SendTexture();
	SendData();


	glDrawElements(GL_TRIANGLES, model->GetNumIndice(), GL_UNSIGNED_INT, 0);
	
	SendRest();
	glEnable(GL_DEPTH_TEST);
}

void Pass::SendAttribute()
{
	if(shader->a_locPosition != -1)
	{
		glEnableVertexAttribArray(shader->a_locPosition);
		glVertexAttribPointer(shader->a_locPosition, sizeof(Vector3)/sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, pos));
	}

	if(shader->a_locTextcoord != -1)
	{
		glEnableVertexAttribArray(shader->a_locTextcoord);
		glVertexAttribPointer(shader->a_locTextcoord, sizeof(Vector2)/sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, textcoord));
	}
}

void Pass::SendTexture()
{
	int texUnit = 0;
	for(int i = 0; i < 3; i++)
	{
		if(texSource[i].fbo != 0)
		{
			if(shader->u_texture2D[texUnit] != -1)
			{
				glActiveTexture(GL_TEXTURE0 + texUnit);

				if(texSource[i].texType == COLOR_TEXTURE)
				{
					glBindTexture(GL_TEXTURE_2D, texSource[i].fbo->colorTexId );
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, texSource[i].fbo->depthTexId );
				}
				glUniform1i(shader->u_texture2D[texUnit], texUnit);
				texUnit++;
			}
		}		
	}
}

void Pass::SendData()
{
	switch(passName)
	{
	case BW:
		break;
	case BLUR:
		if(shader->u_locStep != -1)
		{
			float k = otherData[0];
			float x = 1.0f / Globals::screenWidth;
			float y = 1.0f / Globals::screenHeight;
			float z = sqrt(2.0f) / 2.0f * x;
			float w = sqrt(2.0f) / 2.0f * y;
			glUniform4f(shader->u_locStep, k * x, k * y, k * z, k * w);
		}
		break;
	case PREBLOOM:
		if(shader->u_locLimit != -1)
		{
			glUniform1f(shader->u_locLimit, otherData[0]);
		}
		break;
	case POSTBLOOM:
		break;
	case DEPTH_OF_FIELD:

		if(shader->u_locStep != -1)
		{
			float k = otherData[0];
			float x = 1.0f / Globals::screenWidth;
			float y = 1.0f / Globals::screenHeight;
			float z = sqrt(2.0f) / 2.0f * x;
			float w = sqrt(2.0f) / 2.0f * y;
			glUniform4f(shader->u_locStep, k * x, k * y, k * z, k * w);
		}

		if(shader->u_locNear != -1)
		{
			glUniform1f(shader->u_locNear, otherData[1]);
		}

		if(shader->u_locFar != -1)
		{
			glUniform1f(shader->u_locFar, otherData[2]);
		}

		if(shader->u_locFade != -1)
		{
			glUniform1f(shader->u_locFade, otherData[3]);
		}

		if(shader->u_locClarity != -1)
		{
			glUniform1f(shader->u_locClarity, otherData[4]);
		}
		break;
	}

}

void Pass::SendRest()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Pass::~Pass(void)
{
	if(texSource != 0)
	{
		delete[] texSource;
		texSource = 0;
	}

	if(otherData != 0)
	{
		delete[] otherData;
		otherData = 0;
	}
}
