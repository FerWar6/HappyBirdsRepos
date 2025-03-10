#include "EditorMoveTool.h"
#include "Managers/ServiceLocator.h"
#include "Managers/InputManager.h"
#include "Level/LevelEditor.h"
#include "Engine/PreLoader.h"
#include "Objects/Object.h"
EditorMoveTool::EditorMoveTool()
	: UIElement(),
	inputMan(sl::GetInputManager())
{
	sf::Texture& txrRef = sl::GetPreLoader().GetTexture("EditorMove");
	moveSprite.setTexture(txrRef);
	moveSprite.setOrigin(sf::Vector2f(8, 92));
	//	this needs a sprite and three very specific buttons, 
	//	if any of the buttons are pressed itll give controll to move the object in spefific ways
}

void EditorMoveTool::Update()
{
	Object* selObj = sl::GetLevelEditor().GetSelectedObj();
	int increment = 50;
	if (inputMan.GetKeyDownRepeat(ARROW_UP) && selObj) {
		sf::Vector2f newPos = selObj->GetPos();
		newPos.y -= increment;
		selObj->SetPos(newPos);
	}
	if (inputMan.GetKeyDownRepeat(ARROW_DOWN) && selObj) {
		sf::Vector2f newPos = selObj->GetPos();
		newPos.y += increment;
		selObj->SetPos(newPos);
	}
	if (inputMan.GetKeyDownRepeat(ARROW_LEFT) && selObj) {
		sf::Vector2f newPos = selObj->GetPos();
		newPos.x -= increment;
		selObj->SetPos(newPos);
	}
	if (inputMan.GetKeyDownRepeat(ARROW_RIGHT) && selObj) {
		sf::Vector2f newPos = selObj->GetPos();
		newPos.x += increment;
		selObj->SetPos(newPos);
	}
}

void EditorMoveTool::Render(sf::RenderWindow& window)
{
}

void EditorMoveTool::HandleClick()
{
}

bool EditorMoveTool::HoveringOver()
{
	return false;
}
