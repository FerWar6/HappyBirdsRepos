#pragma once
#include "UI/UIElement.h"
#include "SFML/Graphics.hpp"
#include <functional>
class InputManager;
class EditorMoveTool : UIElement
{
public:
	EditorMoveTool();
	void Update() override;
	void Render(sf::RenderWindow& window) override;
	sf::Sprite moveSprite;
	std::function<void()> OnClick;
private:
	InputManager& inputMan;
	void HandleClick();
	bool HoveringOver();
};