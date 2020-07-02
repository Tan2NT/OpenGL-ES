#pragma once

enum INPUT_KEY_CODE{
	KEY_CAMERA_ROTATE_LEFT = 37,	
	KEY_CAMERA_ROTATE_RIGHT = 39,
	KEY_CAMERA_ROTATE_UP = 38,
	KEY_CAMERA_ROTATE_DOWN = 40,

	KEY_CAMERA_MOVE_LEFT = 65,		// key A
	KEY_CAMERA_MOVE_RIGHT = 68,		// key D
	KEY_CAMERA_MOVE_FORWARD = 83,	// key W
	KEY_CAMERA_MOVE_BACKWARD = 87,	// key S
	KEY_CAMERA_MOVE_UP = 69,		// key E
	KEY_CAMERA_MOVE_DOWN = 81,		// key Q

	KEY_OBJ_MOVE_FORWARD = 33,
	KEY_OBJ_MOVE_BACKWARD = 33,
	KEY_OBJ_MOVE_LEFT = 33,
	KEY_OBJ_MOVE_RIGHT = 33,
	KEY_OBJ_MOVE_UP = 33,
	KEY_OBJ_MOVE_DOWN = 33
};

class Globals
{
public:
	static int screenWidth;
	static int screenHeight;
};