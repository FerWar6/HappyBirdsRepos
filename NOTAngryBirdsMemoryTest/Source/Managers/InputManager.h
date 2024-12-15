#pragma once
#include "Managers/LevelManager.h"
class InputManager
{
public:
	InputManager();
	void InputCheck();
	bool IsClicking();
	bool clicked;
	LevelManager* levelManager;
private:

};

