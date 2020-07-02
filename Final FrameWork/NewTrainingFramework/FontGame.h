#pragma once

#include "Object.h"
#include "Math.h"
#include "Shaders.h"

#define MAX_FONTGAME	5

struct FontData{
	int charCode;
	Vector2 texcoordData[4];
	float x, y, width, height;
};

struct FontVertex{
	float x, y, width, height;
	Vector2 textcoord;
	Vector2 position;

};

class FontGame
{
public:
	Texture *fontTex;
	FontData *fontData;
	Shaders *fontShader;
	int numberOfChar;
	FontVertex fontRectangle[5];

	void InitFontTexture(const char* texFilePath);
	void LoadFontData(const char* filePath);
	void DrawString(float x, float y, float width, float height, float space, const char* string);			// Draw a string from position (x, y) with spacing between letter
	void DrawRectangle(float x, float y, float width, float height);	// Draw an rectangle
	int FindCharCode(int charCode);
	FontGame(void);
	~FontGame(void);
};
