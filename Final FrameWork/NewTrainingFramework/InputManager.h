#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Singleton.h"
#define KEY_A				'A'
#define KEY_D				'D'
#define KEY_S				'S'
#define KEY_W				'W'
#define KEY_RIGHT			37
#define KEY_UP				38
#define KEY_LEFT			39
#define KEY_DOWN			40
#define KEY_SWITCH_EFFECT	' '
#define KEY_SCREEN			'1'
#define KEY_BLUR			'2'
#define KEY_BLOOM			'3'
#define KEY_DOF				'4'
#define KEY_GRAY			'5'

class InputManager : public Singleton<InputManager>
{
public:
	bool keyState[256];
	bool is_KeyPressed;
	unsigned char keyCode;
	bool IsKeyPressed(unsigned char bkeyCode, bool bisKeyPressed);
	bool IsKeyDown(unsigned char bkeyCode);
	InputManager(void);
	~InputManager(void);
};
