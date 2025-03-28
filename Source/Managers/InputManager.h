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

	bool GetScrollWheel(ScrollWheelState state);
	
	bool GetKeyDown(KeyCode key);
	bool GetKeyDownRepeat(KeyCode key);
	bool GetKeyUp(KeyCode key);
	bool GetKey(KeyCode key);
	
	void HandleEvent(const sf::Event& event); // Used for scroll wheel detection
	void SetWindow(sf::RenderWindow& win);
	ButtonManager buttonMan;
	std::string& GetTextInput();
private:
	std::string textInput;
	ScrollWheelState wheelState; // The state of the mouse scroll wheel
	float scrollDelta = 0.0f;

	sf::RenderWindow* window;
	
	sf::Vector2i mousePos;
	sf::Vector2i oldMousePos;

	void InstantiateInputKeys(); // Creates an inputkey for each element in the KeyCode enum
	std::vector<InputKey> inputKeys;
};