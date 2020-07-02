#include "StdAfx.h"
#include "FontGame.h"

FontGame::FontGame(void)
{
	fontData = 0;
	fontTex = 0;
	fontTex = new Texture();
	fontShader = 0;
	fontShader = new Shaders();
	numberOfChar = 0;
	fontShader->Init("../Resources/Shaders/FontShader.vs", "../Resources/Shaders/FontShader.fs");
}

void FontGame::InitFontTexture(const char *texFilePath)
{
	fontTex->Init(texFilePath, GL_REPEAT);
}

void FontGame::LoadFontData(const char* filePath)
{
	fstream fontFile;
	fontFile.open(filePath);
	if(fontFile)
	{
		printf_s(" \n Font file : %s has sucess open", filePath); 
		string lineData;

		while(!fontFile.eof())
		{
			getline(fontFile, lineData);
			//chars count=95
			//char id=32   x=84    y=21    width=3     height=1     xoffset=-1    yoffset=31    xadvance=7     page=0  chnl=15
			if(lineData.find(string("chars count=")) == 0)
			{
				sscanf_s(lineData.data(), "chars count=%d", &numberOfChar);
				fontData = new FontData[numberOfChar];

				for(int i = 0; i <numberOfChar; i++)
				{
					getline(fontFile, lineData);
					sscanf_s(lineData.data(), "char id=%d   x=%d    y=%d    width=%d     height=%d", &fontData[i].charCode, &fontData[i].x, &fontData[i].y, &fontData[i].width, &fontData[i].height);
					printf_s(" \n char id=%d   x=%d    y=%d    width=%d     height=%d", fontData[i].charCode, fontData[i].x, fontData[i].y, fontData[i].width, fontData[i].height);
				}
			}
		}
	}
	else
	{
		printf_s(" \n fail to open : %s file", filePath); 
	}
}

int FontGame::FindCharCode(int charCode)
{
	int i = 0;
	while((fontData[i].charCode != charCode) && (i < numberOfChar))
	{
		i++;
	}

	if( i < numberOfChar)
	{
		return i;
	}
	else
	{
		return -1;
	}
}
void FontGame::DrawString(float x, float y, float width, float height, float space, const char* string)
{
	glUseProgram(fontShader->program);
	glDisable(GL_DEPTH_TEST);

	int strLength = strlen(string);

	for(int i = 0; i < strLength; i++)
	{
		int charCode = string[i];
		int index = FindCharCode(charCode);

		if(index != -1)
		{
			fontRectangle[0].textcoord.x = fontData[index].x / 255;
			fontRectangle[0].textcoord.y = fontData[index].y / 255;

			fontRectangle[1].textcoord.x = (fontData[index].x + fontData[index].width) / 255;
			fontRectangle[1].textcoord.y = fontData[index].y / 255;

			fontRectangle[2].textcoord.x = (fontData[index].x + fontData[index].width) / 255;
			fontRectangle[2].textcoord.y = (fontData[index].y + fontData[index].height) / 255;

			fontRectangle[3].textcoord.x = fontData[index].x / 255;
			fontRectangle[3].textcoord.y = (fontData[index].y + fontData[index].height) / 255;
			
			DrawRectangle(x + i * width + space, y, width, height); 
		}
	}	
}

void FontGame::DrawRectangle(float x, float y, float width, float height)
{
	// Init Rectangle Model
	GLuint vBoid, iBoid;
	int numIndices = 6;
	int numVertex = 4;

	fontRectangle[0].position.x = x;
	fontRectangle[0].position.y = y;

	fontRectangle[1].position.x = x + width;
	fontRectangle[1].position.y = y;

	fontRectangle[2].position.x = x + width;
	fontRectangle[2].position.y = y + height;

	fontRectangle[3].position.x = x;
	fontRectangle[3].position.y = y + height;

	int indiceData[] = {
		0, 1, 2, 
		0, 2, 3
	};

	glGenBuffers(1, &vBoid);
	glBindBuffer(GL_ARRAY_BUFFER, vBoid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(FontVertex) * numVertex , fontRectangle, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Bind data to object buffer
	glGenBuffers(1, &iBoid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBoid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,  numIndices * sizeof(int) , indiceData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vBoid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iBoid);

	// Send Attribute and uniform
	if(fontShader->a_locPosition != -1)
	{
		glEnableVertexAttribArray(fontShader->a_locPosition);
		glVertexAttribPointer(fontShader->a_locPosition, sizeof(Vector2)/sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(FontVertex, position));
	}

	if(fontShader->a_locTextcoord != -1)
	{
		glEnableVertexAttribArray(fontShader->a_locTextcoord);
		glVertexAttribPointer(fontShader->a_locTextcoord, sizeof(Vector2)/sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(FontVertex, textcoord));
	}

	if(fontShader->u_texture2D[0] != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fontTex->textureID);
		glUniform1i(fontShader->u_texture2D[0], 0);
	}

	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
}

FontGame::~FontGame(void)
{
	Texture *fontTex;
	FontData *fontData;
	Shaders *fontShader;
	if(fontShader != 0)
	{
		delete fontShader;
		fontShader = 0;
	}

	if(fontTex != 0)
	{
		delete fontTex;
		fontTex = 0;
	}

	if(fontData != 0)
	{
		delete fontData;
		fontData = 0;
	}
}
