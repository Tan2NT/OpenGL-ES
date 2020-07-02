#pragma once
#include "../Utilities/utilities.h"
#include <vector>

#define MAX_TEXTURE_UNIFORM 4

class Shaders 
{
private:
	GLuint	m_vertexShader, m_fragmentShader;
	GLuint	m_program;
	int		m_id;
public:
	std::vector<GLuint> m_states;

	//Store location of attributes/uniforms
	GLint	a_posL;
	GLint	a_uv;

	GLint	u_mvpMatrix;
	GLint	u_texsLocation[MAX_TEXTURE_UNIFORM];

	int		Init(char * fileVertexShader, char * fileFragmentShader);
	void	EnableState();
	void	DisableState();
	
	void	SetShadersId(int id) { m_id = id;  }
	int		GetShadersId()	{ return m_id; };
	GLuint	GetProgram()	{ return m_program; }

	Shaders();
	~Shaders();
};