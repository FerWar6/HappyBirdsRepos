#pragma once
#include "DataTypes/Enums/KeyCode.h"
#include "DataTypes/Clock.h"
enum KeyState {
	DOWN,
	DOWN_IDLE,
	DOWN_REPEAT,
	UP,
	UP_IDLE
};
struct InputKey {
	InputKey(KeyCode c) 
		: keyCode(c),
		state(UP_IDLE),
		clock() {}
	KeyCode keyCode;
	KeyState state;
	Clock clock;
};