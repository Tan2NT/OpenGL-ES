#include <stdafx.h>
#include "Shaders.h"

Shaders::Shaders():
m_states(NULL)
{
	m_id = 0;
}

int Shaders::Init(char * fileVertexShader, char * fileFragmentShader)
{
	//Create shaders and get his handle 
	m_vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	//check if the compilation of the shader succeeded
	if (m_vertexShader == 0)
		return -1;

	m_fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if (m_fragmentShader == 0)
	{
		glDeleteShader(m_vertexShader);
		return -2;
	}

	//Create a program
	m_program = esLoadProgram(m_vertexShader, m_fragmentShader);

	//finding location of uniforms / attributes
	a_posL = glGetAttribLocation(m_program, "a_posL");
	a_uv = glGetAttribLocation(m_program, "a_uv");

	u_mvpMatrix = glGetUniformLocation(m_program, "u_mvpMat");

	for (int i = 0; i < MAX_TEXTURE_UNIFORM; i++)
	{
		char uniformTexName[20];
		sprintf(uniformTexName, "u_texture%d", i);
		u_texsLocation[i] = glGetUniformLocation(m_program, uniformTexName);
	}

	return 0;
}

void Shaders::EnableState()
{
	for (std::vector<GLuint>::iterator it = m_states.begin(); it != m_states.end(); it++)
	{
		glEnable(*it);
	}
}

void Shaders::DisableState()
{
	for (std::vector<GLuint>::iterator it = m_states.begin(); it != m_states.end(); it++)
	{
		glDisable(*it);
	}
}

Shaders::~Shaders()
{
	glDeleteProgram(m_program);
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
	m_states.clear();
}