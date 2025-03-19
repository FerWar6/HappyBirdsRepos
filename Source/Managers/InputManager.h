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
	
	bool GetScrollWheel(ScrollWheelState state);
	
	bool GetKeyDown(KeyCode key);
	bool GetKeyDownRepeat(KeyCode key);
	bool GetKeyUp(KeyCode key);
	bool GetKey(KeyCode key);
	
	void HandleEvent(const sf::Event& event);
	void SetWindow(sf::RenderWindow& win);
	ButtonManager buttonMan;
private:
	ScrollWheelState wheelState; //the state of the mouse scroll wheel
	float scrollDelta = 0.0f;

	sf::RenderWindow* window;
	
	sf::Vector2i mousePos;
	sf::Vector2i oldMousePos;

	void InstantiateInputKeys();
	std::vector<InputKey> inputKeys;
};