#include "EditorMoveTool.h"
#include "Managers/ServiceLocator.h"
#include "Managers/InputManager.h"
#include "Engine/Scenes/SceneEditor.h"
#include "Engine/PreLoader.h"
#include "Objects/Object.h"
#include <math.h>

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
				if (moveSprite == &moveSpriteX)
				{
					std::function<void()> func = std::bind(&EditorMoveTool::SetCurrentMode, this, MOVEMODE_X);
					inputMan.buttonMan.AddButtonCall(EDITOR, func);
				}
				if (moveSprite == &moveSpriteY)
				{
					std::function<void()> func = std::bind(&EditorMoveTool::SetCurrentMode, this, MOVEMODE_Y);
					inputMan.buttonMan.AddButtonCall(EDITOR, func);
				}
				if (moveSprite == &moveSpriteXY)
				{
					std::function<void()> func = std::bind(&EditorMoveTool::SetCurrentMode, this, MOVEMODE_XY);
					inputMan.buttonMan.AddButtonCall(EDITOR, func);
				}
			}
		}
	}
	if (inputMan.GetKeyUp(MOUSE_L) && selectedObj) {
		currentMode = MOVEMODE_IDLE;
	}
	switch (currentMode) {
		case MOVEMODE_X: {
			sf::Vector2f newPos;
			if (intervalMode()) {
				float xpos = round((inputMan.GetMousePos().x + mouseOffset.x) / interval) * interval;
				newPos = sf::Vector2f(xpos, selectedObj->GetPos().y);
			}
			else {
				newPos = sf::Vector2f(inputMan.GetMousePos().x + mouseOffset.x, selectedObj->GetPos().y);
			}
			selectedObj->SetPos(newPos);
			break;
		}

		case MOVEMODE_Y: {
			sf::Vector2f newPos;
			if (intervalMode()) {
				float ypos = round((inputMan.GetMousePos().y + mouseOffset.y) / interval) * interval;
				newPos = sf::Vector2f(selectedObj->GetPos().x, ypos);
			}
			else {
				newPos = sf::Vector2f(selectedObj->GetPos().x, inputMan.GetMousePos().y + mouseOffset.y);
			}
			selectedObj->SetPos(newPos);
			break;
		}

		case MOVEMODE_XY: {
			sf::Vector2f newPos;
			if (intervalMode()) {
				float xpos = round((inputMan.GetMousePos().x + mouseOffset.x) / interval) * interval;
				float ypos = round((inputMan.GetMousePos().y + mouseOffset.y) / interval) * interval;
				newPos = sf::Vector2f(xpos, ypos);
			}
			else {
				newPos = sf::Vector2f((sf::Vector2f)(inputMan.GetMousePos()) + mouseOffset);
			}
			selectedObj->SetPos(newPos);
			break;
		}

		default:
			break;
	}

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

bool EditorMoveTool::intervalMode()
{
	return inputMan.GetKey(CONTROL);
}

EditorMoveToolMode& EditorMoveTool::GetCurrentMode()
{
	return currentMode;
}

void EditorMoveTool::SetCurrentMode(EditorMoveToolMode newMode)
{
	mouseOffset = selectedObj->GetPos() - (sf::Vector2f)inputMan.GetMousePos();
	currentMode = newMode;
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
