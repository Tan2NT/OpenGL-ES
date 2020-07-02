                                                                                     #include "stdafx.h"
#include "Texture.h"


Texture::Texture()
{
	m_textureHandle = 0;
	m_Id = 0;
	m_target = GL_TEXTURE_2D;
}


Texture::~Texture()
{
	glDeleteTextures(1, &m_textureHandle);
}

void Texture::Init2DTexture(char* path)
{
	m_target = GL_TEXTURE_2D;
	// Gererate a texture object
	glGenTextures(1, &m_textureHandle);
	
	//bind the texture object to operator
	glBindTexture(m_target, m_textureHandle);

	//read an image data
	int w, h, bpp;
	char* pixels = LoadTGA(path, &w, &h, &bpp);
	
	if (pixels != NULL)
	{
		if (bpp == 24)
		{
			//load the texture
			glTexImage2D(m_target, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		}
		else
		{
			//load the texture
			glTexImage2D(m_target, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		}

		//Set the filtering mode
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, m_tilingMode);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, m_tilingMode);

		glGenerateMipmap(m_target);
	}

	glBindTexture(m_target, 0);
	
}

char* ExtractFace(char * bufferTGA, int width, int height, int widthOffset, int heightOffset, int bpp)
{
	int startX = widthOffset * bpp / 8;
	int startY = heightOffset;
	int noElementSubBufferTGA = (width / 4) * (height / 3) * bpp / 8;
	char * subBufferTGA = new char[noElementSubBufferTGA];

	int sizecpy = (width / 4) * (bpp / 8);
	for (int y = startY; y < startY + (height / 3); y++)
	{
		int indexBufferTGA = (y  * width * (bpp / 8)) + (widthOffset)* (bpp / 8);
		memcpy(&subBufferTGA[(y - startY) * sizecpy], &bufferTGA[indexBufferTGA], sizecpy);
	}
	return subBufferTGA;
}

void Texture::InitCubeTexture(char* path)
{
	m_target = GL_TEXTURE_CUBE_MAP;
	// Gererate a texture object
	glGenTextures(1, &m_textureHandle);

	//bind the texture object to operator
	glBindTexture(m_target, m_textureHandle);

	// create CPU buffer and load it with the image data
	int width, height, bpp;
	char * bufferTGA = LoadTGA(path, &width, &height, &bpp);
	char **subBufferTGA = new char *[6];

	// sub 0 +x
	int widthOffset = 2 * (width / 4);
	int heightOffset = (height / 3);
	subBufferTGA[0] = ExtractFace(bufferTGA, width, height, widthOffset, heightOffset, bpp);

	// sub 1 -x
	widthOffset = 1;
	heightOffset = (height / 3);
	subBufferTGA[1] = ExtractFace(bufferTGA, width, height, widthOffset, heightOffset, bpp);

	// sub 2 +y
	widthOffset = (width / 4);
	heightOffset = 1;
	subBufferTGA[2] = ExtractFace(bufferTGA, width, height, widthOffset, heightOffset, bpp);

	// sub 3 -y
	widthOffset = (width / 4);
	heightOffset = 2 * (height / 3);
	subBufferTGA[3] = ExtractFace(bufferTGA, width, height, widthOffset, heightOffset, bpp);

	// sub 4 +z
	widthOffset = (width / 4);
	heightOffset = (height / 3);
	subBufferTGA[4] = ExtractFace(bufferTGA, width, height, widthOffset, heightOffset, bpp);

	// sub 5 -z
	widthOffset = 3 * (width / 4);
	heightOffset = (height / 3);
	subBufferTGA[5] = ExtractFace(bufferTGA, width, height, widthOffset, heightOffset, bpp);


	// load the image data into OpenGL ES texture resource
	for (int i = 0; i < 6; i++)
	{
		if (bpp == 24)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width / 4, height / 3, 0, GL_RGB, GL_UNSIGNED_BYTE, subBufferTGA[i]);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width / 4, height / 3, 0, GL_RGBA, GL_UNSIGNED_BYTE, subBufferTGA[i]);
		}
	}


	if (bufferTGA != 0)
	{
		delete[] bufferTGA;
		bufferTGA = 0;
	}

	for (int i = 0; i< 6; i++)
	{
		if (subBufferTGA[i] != 0)
		{
			delete[] subBufferTGA[i];
			subBufferTGA[i] = 0;
		}
	}

	if (subBufferTGA != 0)
	{
		delete[] subBufferTGA;
		subBufferTGA = 0;
	}

	//set the filters for minification and magnification
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// generate the mipmap chain
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	//set the wrapping modes
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, m_tilingMode);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, m_tilingMode);
	}
}
