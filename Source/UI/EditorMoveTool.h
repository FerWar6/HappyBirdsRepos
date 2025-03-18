#pragma once
#include "UI/UIElement.h"
#include "SFML/Graphics.hpp"
#include <functional>
class InputManager;
class Object;
enum EditorMoveToolMode {
	MOVEMODE_IDLE,
	MOVEMODE_X,
	MOVEMODE_Y,
	MOVEMODE_XY
};
class EditorMoveTool : UIElement
{
public:
	EditorMoveTool(Object*& selObj);
	void Update() override;
	void Render(sf::RenderWindow& window) override;
	sf::Sprite moveSpriteX;
	sf::Sprite moveSpriteY;
	sf::Sprite moveSpriteXY;
	std::vector<sf::Sprite*> moveSprites;
	std::function<void()> OnClick;
	EditorMoveToolMode currentMode;
private:
	Object*& selectedObj;
	InputManager& inputMan;
	void HandleClick();
	bool HoveringOver(sf::FloatRect rect);
};
