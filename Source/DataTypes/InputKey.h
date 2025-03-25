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
enum ScrollWheelState {
	SCROLL_IDLE = 0,
	SCROLL_UP = 1,
	SCROLL_DOWN = -1
};
struct InputKey { // an inputkey has a current state, a keycode like A or MOUSE_L to determain what key it is and a clock for repeat usage
	InputKey(KeyCode c) 
		: keyCode(c),
		state(UP_IDLE),
		clock() {}
	KeyCode keyCode;
	KeyState state;
	Clock clock;
};