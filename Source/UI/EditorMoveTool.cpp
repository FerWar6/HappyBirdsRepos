#include "EditorMoveTool.h"
#include "Managers/ServiceLocator.h"
#include "Managers/InputManager.h"
#include "Engine/Scenes/SceneEditor.h"
#include "Engine/PreLoader.h"
#include "Objects/Object.h"
EditorMoveTool::EditorMoveTool(Object*& selObj)
	: UIElement(),
	selectedObj(selObj),
	inputMan(sl::GetInputManager()),
	currentMode(MOVEMODE_IDLE)
{
	moveSpriteX.setTexture(sl::GetPreLoader().GetTexture("EditorMoveToolX"));
	moveSpriteY.setTexture(sl::GetPreLoader().GetTexture("EditorMoveToolY"));
	moveSpriteXY.setTexture(sl::GetPreLoader().GetTexture("EditorMoveToolXY"));
	moveSpriteX.setOrigin(sf::Vector2f(-26, 10));
	moveSpriteY.setOrigin(sf::Vector2f(5, 95));
	moveSpriteXY.setOrigin(sf::Vector2f(5, 26));
	moveSprites.push_back(&moveSpriteX);
	moveSprites.push_back(&moveSpriteY);
	moveSprites.push_back(&moveSpriteXY);
	

	//	this needs a sprite and three very specific buttons, 
	//	if any of the buttons are pressed itll give controll to move the object in spefific ways
}

void EditorMoveTool::Update()
{
	int increment = 50;
	if (inputMan.GetKeyDownRepeat(ARROW_UP) && selectedObj) {
		sf::Vector2f newPos = selectedObj->GetPos();
		newPos.y -= increment;
		selectedObj->SetPos(newPos);
	}
	if (inputMan.GetKeyDownRepeat(ARROW_DOWN) && selectedObj) {
		sf::Vector2f newPos = selectedObj->GetPos();
		newPos.y += increment;
		selectedObj->SetPos(newPos);
	}
	if (inputMan.GetKeyDownRepeat(ARROW_LEFT) && selectedObj) {
		sf::Vector2f newPos = selectedObj->GetPos();
		newPos.x -= increment;
		selectedObj->SetPos(newPos);
	}
	if (inputMan.GetKeyDownRepeat(ARROW_RIGHT) && selectedObj) {
		sf::Vector2f newPos = selectedObj->GetPos();
		newPos.x += increment;
		selectedObj->SetPos(newPos);
	}
	if (inputMan.GetKeyDown(MOUSE_L) && selectedObj) {
		for (auto moveSprite : moveSprites) {
			if (HoveringOver(moveSprite->getGlobalBounds())) {
				if (moveSprite == &moveSpriteX) currentMode = MOVEMODE_X;
				if (moveSprite == &moveSpriteY) currentMode = MOVEMODE_Y;
				if (moveSprite == &moveSpriteXY) currentMode = MOVEMODE_XY;
			}
		}
	}
	if (inputMan.GetKeyUp(MOUSE_L) && selectedObj) {
		currentMode = MOVEMODE_IDLE;
	}
	std::cout << currentMode << "\n";
}

void EditorMoveTool::Render(sf::RenderWindow& window)
{
	if (selectedObj) {
		for (auto& moveSprite : moveSprites) {
			moveSprite->setPosition(selectedObj->GetPos());
			if (HoveringOver(moveSprite->getGlobalBounds())) moveSprite->setColor(sf::Color(155, 155, 155));
			else moveSprite->setColor(sf::Color(255, 255, 255));
			window.draw(*moveSprite);
		}
	}
}

void EditorMoveTool::HandleClick()
{

}

bool EditorMoveTool::HoveringOver(sf::FloatRect rect)
{
	sf::Vector2i mP = inputMan.GetMousePos();
	sf::Vector2i p = (sf::Vector2i)rect.getPosition();
	sf::Vector2i s = (sf::Vector2i)rect.getSize();
	return mP.x > p.x && mP.x < p.x + s.x && mP.y > p.y && mP.y < p.y + s.y;
}
