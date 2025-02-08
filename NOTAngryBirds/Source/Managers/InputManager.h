#pragma once
#include "Managers/ButtonManager.h"
#include "DataTypes/InputKey.h"
#include "SFML/Graphics.hpp"
class Engine;
class Camera;
class InputManager
{
public:
	InputManager();
	void UpdateInputs();
	void SetMousePos(sf::RenderWindow& win);
	sf::Vector2i mousePos;
	sf::Vector2i oldMousePos;
	bool GetKeyDown(KeyCode key);
	bool GetKeyDownRepeat(KeyCode key);
	bool GetKeyUp(KeyCode key);
	bool GetKey(KeyCode key);
	
	void SetWindow(sf::RenderWindow& win);
	ButtonManager buttonManager;
private:
	sf::RenderWindow* window;
	
	void InstantiateInputKeys();
	std::vector<InputKey> inputKeys;
};