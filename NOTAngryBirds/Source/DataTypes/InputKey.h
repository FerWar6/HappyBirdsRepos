#pragma once
#include "DataTypes/Enums/KeyCode.h"
struct InputKey {
	InputKey(KeyCode c) 
		: code(c),
		isPressed(false) {}
	KeyCode code;
	bool isPressed;
};