#include "StdAfx.h"
#include "CubeTexture.h"

CubeTexture::CubeTexture(void)
{
	textureID = 0; 
}

GLubyte* CubeTexture::GetSubBuffer(char *pScrBuffer, int x, int y, int offsetX, int offsetY, int width, int height, int chanel)
{
	int nScrBuffer = width * height * chanel;

	int outBufferSize = offsetX * offsetY * chanel;
	GLubyte *pOutBuffer = new GLubyte[outBufferSize];
	int outBufferCount = 0;
	
	if((x + offsetX > width) || (y + offsetY > height))
	{
		printf("\n the size of Sub CubeTexture is out of range "); 
		return NULL;
	}

	for(int i = y; i < y + offsetY; i++)
		for(int j = x; j < x + offsetX; j++)
		{
			// A[i, j] = C[width * chanel * i + chanel * j]
			int scrBufferCount = width * chanel * i + chanel * j;

			if(scrBufferCount < nScrBuffer - 2)
			{
				for(int k = 0; k < chanel; k++)
				{
					pOutBuffer[outBufferCount] = pScrBuffer[ scrBufferCount + k];
					outBufferCount += 1;
				}
			}
		}
	
	return pOutBuffer;
}

void CubeTexture::Init(const char* textureFiles, unsigned int TILING)
{
	GLubyte *bufferTGA[6];
	int width, height, bpp;
	char *bufferColor = LoadTGA( textureFiles, &width, &height, &bpp);

	// Gen the texture object
	glGenTextures(1, &textureID);
	
   // Bind the texture object
   glBindTexture ( GL_TEXTURE_CUBE_MAP, textureID );
   
	//set the filters for minification and magnification
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//set the wrapping modes
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, TILING);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, TILING);

	GLuint subWidth = width/4, subHeight = height/3;
	int chanel = bpp == 24 ? 3 : 4;

	// Load the cube face - Positive X
	bufferTGA[0] = GetSubBuffer(bufferColor, width/2, height/3, width/4, height/3, width, height, chanel);	
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA[0]);
	
	// Load the cube face - Negative X
	bufferTGA[1] =  GetSubBuffer(bufferColor, 0, height/3, width/4, height/3, width, height, chanel);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, subWidth, subHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA[1]);
	
	// Load the cube face - Positive Y
	bufferTGA[2] =  GetSubBuffer(bufferColor, width/4, 0, width/4, height/3, width, height, chanel);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, subWidth, subHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA[2]);
	
	// Load the cube face - Negative Y
	bufferTGA[3] =  GetSubBuffer(bufferColor, width/4, 2 * height/3, width/4, height/3, width, height, chanel);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, subWidth, subHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA[3]);
	
	// Load the cube face - Positive Z
	bufferTGA[4] =  GetSubBuffer(bufferColor, width/4, height/3, width/4, height/3, width, height, chanel);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, subWidth, subHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA[4]);
	
	// Load the cube face - Negative Z
	bufferTGA[5] =  GetSubBuffer(bufferColor, 3 * width/4, height/3, width/4, height/3, width, height, chanel);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, subWidth, subHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bufferTGA[5]);

	// generate the mipmap chain
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	// free the client memory
	for(int i = 0; i < 6; i++)
	{
		delete bufferTGA[i];
		bufferTGA[i] = NULL;
	}

	delete bufferColor;
	bufferColor = 0;
}

CubeTexture::~CubeTexture(void)
{
	if( this->textureID != 0 )
	{
		glDeleteTextures(1, &textureID );
		textureID = 0;
	}
}