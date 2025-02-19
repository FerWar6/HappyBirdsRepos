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

	const sf::Vector2i& GetMousePos();
	void SetMousePos(sf::RenderWindow& win);
	void UpdateMousePos();

	const sf::Vector2i& GetOldMousePos();
	void SetOldMousePos(sf::RenderWindow& win);
	void UpdateOldMousePos();
	
	bool GetKeyDown(KeyCode key);
	bool GetKeyDownRepeat(KeyCode key);
	bool GetKeyUp(KeyCode key);
	bool GetKey(KeyCode key);
	
	void SetWindow(sf::RenderWindow& win);
	ButtonManager buttonManager;
private:
	sf::RenderWindow* window;
	
	sf::Vector2i mousePos;
	sf::Vector2i oldMousePos;

	void InstantiateInputKeys();
	std::vector<InputKey> inputKeys;
};