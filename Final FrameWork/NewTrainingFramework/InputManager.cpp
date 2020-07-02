#include "StdAfx.h"
#include "InputManager.h"

InputManager::InputManager(void)
{
	is_KeyPressed = false;
	memset(keyState, false, sizeof(keyState));
}

bool InputManager::IsKeyPressed(unsigned char bkeyCode, bool bisPressed)
{
	if(bisPressed)
	{
		keyCode = bkeyCode;
		keyState[bkeyCode] = true;
		is_KeyPressed = bisPressed;
		return true;
	}
	else
	{
		is_KeyPressed = false;
		keyState[bkeyCode] = false;
		return false;
	}
}

bool InputManager::IsKeyDown(unsigned char bkeyCode)
{
	if( keyState[bkeyCode])
		return true;
	else
		return false;
}

InputManager::~InputManager(void)
{
}
