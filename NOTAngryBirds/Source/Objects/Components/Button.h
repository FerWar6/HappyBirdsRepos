#pragma once
#include "Objects/Components/Component.h"
#include <functional>

class InputManager;
struct Button : public Component
{
	Button(std::function<void()> onClick, InputManager& inputM);
	~Button();
	std::function<void()> OnClick;
	sf::Vector2i& mousePos;
private:
	InputManager& inputMan;
	void HandleClick();
};