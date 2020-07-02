#include "stdafx.h"
#include "Model.h"
#include <iostream>


Model::Model()
{
	m_modelId = -1;
	m_vboId = 0;
	m_iboId = 0;
	m_numOfIndices = m_numOfVertices = 0;
}


Model::~Model()
{
	glDeleteBuffers(1, &m_vboId);
	glDeleteBuffers(1, &m_iboId);
}

void Model::Init(char* path)
{
	FILE * f = fopen(path, "r");

	if (f == NULL)
	{
		esLogMessage("fail to open model %s", path);
		return;
	}

	int index = 0;
	float temp;

	// Read Vetices Data
	fscanf_s(f, "NrVertices: %d\n", &m_numOfVertices);
	Vertex *verticesData = new Vertex[m_numOfVertices];
	int x;
	for (index = 0; index < m_numOfVertices; index++)
	{
		fscanf(f, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n",
			&x, &verticesData[index].pos.x, &verticesData[index].pos.y, &verticesData[index].pos.z, &temp, &temp, &temp, &temp, &temp, &temp, &temp, &temp, &temp, &verticesData[index].texcoord.x, &verticesData[index].texcoord.y);
		//std::cout << "\n" << x << ". pos: " << verticesData[index].pos.x << " - " << verticesData[index].pos.y << " - " << verticesData[index].pos.z;
	}


	// Indices data
	int numOfTriangle;
	fscanf_s(f, "NrIndices: %d\n", &m_numOfIndices);
	unsigned int *indices = new unsigned int[m_numOfIndices];
	int a, b, c;
	int idx = -1;
	for (index = 0; index < (int)m_numOfIndices / 3; index++)
	{
		fscanf(f, "%d.  %d,  %d,  %d\n", &x, &indices[3 * index], &indices[3 * index + 1], &indices[3 * index + 2]);
		//std::cout << "\n" << x << ". pos: " << m_indices[3 * index] << " - " << m_indices[3 * index + 1] << " - " << m_indices[3 * index + 2];
	}

	fclose(f);

	// Create buffer object then bind vertex data to this buffer
	glGenBuffers(1, &m_vboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_numOfVertices, verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &m_iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* m_numOfIndices, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
