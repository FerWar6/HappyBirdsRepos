#pragma once
#include "Level/LevelManager.h"
#include "Events/Event.h"
class Engine;
class InputManager
{
public:
	InputManager(Engine* engine);
	void InputCheck();
	bool IsClicking();
	bool clicked;
	sf::Vector2i cursorPos;

	Event<void> onMouseLeftDown; //left is 1, middle is 2 and right is 3
private:
	Engine* enginePtr;
};

