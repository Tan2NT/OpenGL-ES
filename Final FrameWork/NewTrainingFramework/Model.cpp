#include "StdAfx.h"
#include "Model.h"

Model::Model(void)
{
	indiceData = 0;
	vertexData = 0;
	vBoid = 0;
	iBoid = 0;
}
//
//long getFileSize(FILE *file)
//{
//	long lCurPos, lEndPos;
//	lCurPos = ftell(file);
//	fseek(file, 0, 2);
//	lEndPos = ftell(file);
//	fseek(file, lCurPos, 0);
//	return lEndPos;
//}
//
//GLubyte* GetImageData(const char* filePath)
//{	
//	// Pointer to our buffered data
//	FILE *file = NULL;      // File pointer
//
//	// Open the file in binary mode using the "rb" format string
//	// This also checks if the file exists and/or can be opened for reading correctly
//	fopen_s(&file, filePath, "rb");
//	if (file == NULL)
//		cout << "Could not open specified file" << endl;
//	else
//		cout << "File opened successfully" << endl;
//
//	// Get the size of the file in bytes
//	long fileSize = getFileSize(file);
//
//	GLubyte* bufferColor = new GLubyte[fileSize];
//	fread(bufferColor, fileSize, 1, file);
//
//	for(int i = 0; i < 128 * 128; i++)
//	{
//		if(i % 4 == 0)
//		{
//			printf("\n");
//		}
//		printf("  %d  ", bufferColor[i]);
//	}
//
//	return bufferColor;
//}

void Model::Init( const char* filePath)
{
	//Read data from NFG file
	char *heightMapData;
	bool isHeightMap = false;
	int width, height, bpp;
	if(strcmp( filePath, "../Resources/Model/Terrain.nfg") == 0)
	{
		heightMapData = LoadTGA("../Resources/Textures/heightmap.tga", &width, &height, &bpp );//GetImageData("../Resources/Textures/heightmap.raw");
		isHeightMap = true;
	}

	ifstream myFile;
	myFile.open(filePath);
	string stringLine;
	int numVertex = 0, numIndices = 0;
	if (myFile.is_open()) 
	{
		cout<<"File is open";

		int count = 0;
		// Get Vertexs Data
		getline(myFile,stringLine);
		sscanf_s(stringLine.data(), "NrVertices: %d", &numVertex);
		vertexData = new Vertex[numVertex];
		for(int i = 0; i < numVertex; i++)
		{
			getline(myFile,stringLine);
			int index;
			sscanf_s(stringLine.data(),"%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];", &index, &vertexData[i].pos.x, &vertexData[i].pos.y, &vertexData[i].pos.z, &vertexData[i].normal.x, &vertexData[i].normal.y, &vertexData[i].normal.z, &vertexData[i].bitangent.x, &vertexData[i].bitangent.y, &vertexData[i].bitangent.z, &vertexData[i].tangent.x, &vertexData[i].tangent.y, &vertexData[i].tangent.z, &vertexData[i].textcoord.x, &vertexData[i].textcoord.y );
			
			
			if(isHeightMap == true)
			{
				int chanel = int (bpp / 8) ;
				float r = heightMapData[ int(chanel * (vertexData[i].textcoord.x * width) + vertexData[i].textcoord.y * height)] / 255.0f; 
				float g = heightMapData[ int(chanel * (vertexData[i].textcoord.x * width) + vertexData[i].textcoord.y * height) + 1] / 255.0f; 
				float b = heightMapData[ int(chanel * (vertexData[i].textcoord.x * width) + vertexData[i].textcoord.y * height) + 2]  / 255.0f; 
				vertexData[i].pos.y = 10.0f *(3 * r + 2 * g + b);
				count++;
			}
		}

		//Get Indices Data
		getline(myFile,stringLine);
		sscanf_s(stringLine.data(), "NrIndices: %d", &numIndice);
		numIndices = numIndice;
		indiceData = new int[numIndice];
		for(int i = 0; i < numIndice/3; i++)
		{
			getline(myFile,stringLine);
			int index;
			sscanf_s(stringLine.data(),"   %d.    %d,    %d,    %d", &index, &indiceData[i * 3], &indiceData[i * 3 + 1], &indiceData[i * 3 + 2] );
		}

		// Bind Vertex Data to a buffer
		glGenBuffers(1, &vBoid);
		glBindBuffer(GL_ARRAY_BUFFER, vBoid);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertex , vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Bind data to object buffer
		glGenBuffers(1, &iBoid);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBoid);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,  numIndices * sizeof(int) , indiceData, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		myFile.close();

		if(isHeightMap == true)
		{
			delete[] heightMapData;
			heightMapData = 0;
		}
	}
	else
	{
		cout<<"file not found";
	}
}

GLuint Model::GetVboil()
{
	return vBoid;
}

GLuint Model::GetIboil()
{
	return iBoid;
}

GLsizei Model::GetNumIndice()
{
	return numIndice;
}

Model::~Model(void)
{
	if(vertexData != 0)
	{
		delete[] vertexData;
		vertexData = 0;
	}
	
	if(indiceData != 0)
	{
		delete[] indiceData;
		indiceData = 0;
	}

	if(vBoid != 0)
	{
		glDeleteBuffers(1, &vBoid);
		vBoid = 0;
	}
	
	if(iBoid != 0)
	{
		glDeleteBuffers(1, &iBoid);
		iBoid = 0;
	}
}
