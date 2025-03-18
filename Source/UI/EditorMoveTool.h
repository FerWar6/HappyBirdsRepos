#pragma once
#include "UI/UIElement.h"
#include "SFML/Graphics.hpp"
#include <functional>
class InputManager;
class Object;
class EditorMoveTool : UIElement
{
public:
	EditorMoveTool(Object*& selObj);
	void Update() override;
	void Render(sf::RenderWindow& window) override;
	sf::Sprite moveSprite;
	sf::Sprite moveSpriteX;
	sf::Sprite moveSpriteY;
	sf::Sprite moveSpriteXY;
	std::function<void()> OnClick;
private:
	Object*& selectedObj;
	InputManager& inputMan;
	void HandleClick();
	bool HoveringOver();
};