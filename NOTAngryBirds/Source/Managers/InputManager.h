#pragma once
#include "Events/Event.h"
#include "DataTypes/InputKey.h"
#include "SFML/Graphics.hpp"
class Engine;
class InputManager
{
public:
	InputManager();
	void UpdateInputs();
	void SetMousePos(sf::RenderWindow& win);
	sf::Vector2i mousePos;
	bool GetKeyDown(KeyCode key);
	bool GetKeyUp(KeyCode key);
	bool GetKey(KeyCode key);

	std::vector<InputKey> inputKeys;
	Event<void> onMouseLeftDown; 
	Event<void> onMouseLeftUp;
	bool mouseLeftClicked;

	Event<void> onMouseRightDown;
	Event<void> onMouseRightUp;
	bool mouseRightClicked;
private:
	void InstantiateInputKeys();
};

