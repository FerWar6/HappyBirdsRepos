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
	sf::Vector2i mousePos;

	bool GetKey(KeyCode key);
	//left is 1, middle is 2 and right is 3
	Event<void> onMouseLeftDown; 
	Event<void> onMouseLeftUp;
	bool mouseLeftClicked;

	Event<void> onMouseRightDown;
	Event<void> onMouseRightUp;
	bool mouseRightClicked;
private:
	Engine* enginePtr;
};

