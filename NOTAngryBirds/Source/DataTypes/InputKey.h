#pragma once
#include "DataTypes/Enums/KeyCode.h"
enum KeyState {
	DOWN,
	DOWN_IDLE,
	UP,
	UP_IDLE
};
struct InputKey {
	InputKey(KeyCode c) 
		: keyCode(c),
		state(UP_IDLE) {}
	KeyCode keyCode;
	KeyState state;
};