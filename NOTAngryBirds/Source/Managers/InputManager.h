#pragma once
#include "Managers/LevelManager.h"

class Engine;
class InputManager
{
public:
	InputManager(Engine* engine);
	void InputCheck();
	bool IsClicking();
	bool clicked;
	sf::Vector2i cursorPos;
private:
	Engine* enginePtr;
};

