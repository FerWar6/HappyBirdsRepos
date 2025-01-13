#pragma once
#include "Events/Event.h"
#include "Engine/Enums/KeyCode.h"
#include "SFML/Graphics.hpp"
class Engine;
class InputManager
{
public:
	InputManager(Engine* engine);
	void InputCheck();
	bool IsClicking();
	bool clicked;
	sf::Vector2i cursorPos;

	bool GetKey(KeyCode key);

	Event<void> onMouseLeftDown; //left is 1, middle is 2 and right is 3
private:
	Engine* enginePtr;
};

