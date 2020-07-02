#include "StdAfx.h"
#include "Texture.h"

Texture::Texture(void)
{
	textureID = 0;
}


void Texture::Init(const char* textureFilePath,  unsigned int TILING)
{
	// create the OpenGL ES texture resource and get the handle
	glGenTextures(1, &textureID);

	// bind the texture to the 2D texture type
	glBindTexture(GL_TEXTURE_2D, textureID);

	// create CPU buffer and load it with the image data
	int width, height, bpp;
	char *bufferTGA = LoadTGA(textureFilePath, &width, &height, &bpp );

	// load the image data into OpenGL ES texture resource
	glTexImage2D(GL_TEXTURE_2D, 0, (bpp == 24 ? GL_RGB : GL_RGBA), width, height, 0, (bpp == 24 ? GL_RGB : GL_RGBA), GL_UNSIGNED_BYTE, bufferTGA);
	delete [] bufferTGA;
	
	//set the filters for minification and magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TILING);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TILING);
	// generate the mipmap chain
	glGenerateMipmap(GL_TEXTURE_2D);
	//set the wrapping modes
}

Texture::~Texture(void)
{
	if( this->textureID != 0 )
	{
		glDeleteTextures(1, &textureID );
		textureID = 0;
	}
}
