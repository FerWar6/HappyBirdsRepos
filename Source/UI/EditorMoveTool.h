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
	int interval = 5; // TODO - add the interval to the scene editor 
	bool intervalMode();
	sf::Vector2f mouseOffset; // the offset that needs to be applied to the obj position 
	EditorMoveToolMode& GetCurrentMode();
	void SetCurrentMode(EditorMoveToolMode newMode);

private:
	EditorMoveToolMode currentMode;
	Object*& selectedObj; // reference to the selectedobject inside of the sceneEditor
	InputManager& inputMan;
	bool HoveringOver(sf::FloatRect rect);
};
